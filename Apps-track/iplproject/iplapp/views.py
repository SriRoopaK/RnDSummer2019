from django.shortcuts import render, redirect
from django.core.paginator import Paginator
from .models import *
# Create your views here.

def home(request):
    context = dict()
    context['seasons'] = list(range(2008, 2020))
    return render(request, 'iplapp/home.html', context)


def season_details(request, year=2019):
    context = dict()
    match_details = Match.objects.filter(season=year)
    paginator = Paginator(match_details, 8)
    page = request.GET.get('page')
    matches = paginator.get_page(page)
    context['year'] = year
    context['matches'] = matches
    context['seasons'] = list(range(2008, 2020))
    return render(request, 'iplapp/season_details.html', context)


def match_report(request, year=2019, match_id=60):
    if request.user.is_authenticated:
        context = dict()
        match_details = Match.objects.get(sl_no=match_id)
        context['match'] = match_details
        ball_details = Deliveries.objects.filter(match_id=match_id)
        inning1 = Deliveries.objects.filter(match_id=match_id).first()
        inning2 = Deliveries.objects.filter(match_id=match_id).filter(inning=2).first()
        records = inning2.id - inning1.id
        paginator = Paginator(ball_details, records)
        page = request.GET.get('page')
        deliveries = paginator.get_page(page)
        context['deliveries'] = deliveries
        return render(request, 'iplapp/match_report.html', context)
    else:
        return redirect('/login/')


def points_table(request, year=2019):
    matches = Match.objects.filter(season=year)
    points = dict()
    for match in matches:
        if match.result == 'normal' or match.result == 'tie':
            if match.winner not in points:
                points[match.winner] = 2
            elif match.winner in points:
                points[match.winner] += 2
        elif match.result == 'no result':
            if match.team1 not in points:
                points[match.team1] = 1
            elif match.team1 in points:
                points[match.team1] += 1
            if match.team2 not in points:
                points[match.team2] = 1
            elif match.team2 in points:
                points[match.team2] += 1
    points_list = list(points.items())
    points_list.sort(key=lambda x: x[1], reverse=True)
    context = dict()
    context['points'] = points_list
    context['years'] = list(range(2008, 2020))
    return render(request, 'iplapp/points.html', context)


def teams(request):
    teams = Match.objects.values_list('team1')
    teams = set(teams)
    context = dict()
    teams_list = list()
    for team in teams:
        team = str(team)
        teams_list.append(team[2:len(team)-3])
    context['teams'] = teams_list
    return render(request, 'iplapp/teams.html', context)


def team_details(request, team_name):
    context = dict()
    context['team'] = team_name
    points_table = list()
    matches_list = list()
    for season in range(2008, 2020):
        points = 0
        matches1 = Match.objects.filter(team1=team_name).filter(season=season)
        matches2 = Match.objects.filter(team2=team_name).filter(season=season)
        for match in matches1:
            if match.winner == 'None':
                points += 1
            elif match.winner == team_name:
                points += 2
        for match in matches2:
            if match.winner == 'None':
                points += 1
            elif match.winner == team_name:
                points += 2
        if points != 0:
            points_table.append((season, points, matches1.count()+matches2.count(), points//2))
        matches_list.append(matches1)
        matches_list.append(matches2)
    context['points'] = points_table
    context['matches'] = matches_list
    return render(request, 'iplapp/team_details.html', context)
