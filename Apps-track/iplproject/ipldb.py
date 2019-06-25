import click
import openpyxl
import django
import os

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'iplproject.settings')
django.setup()


from iplapp.models import Match, Deliveries


def add_delivery_data(data):
    d = Deliveries()
    d.match_id = data[0]
    d.inning = data[1]
    d.batting_team = data[2]
    d.bowling_team = data[3]
    d.over = data[4]
    d.ball = data[5]
    d.batsman = data[6]
    d.non_striker = data[7]
    d.bowler = data[8]
    d.is_super_over = data[9]
    d.wide_runs = data[10]
    d.bye_runs = data[11]
    d.legbye_runs = data[12]
    d.noball_runs = data[13]
    d.penalty_runs = data[14]
    d.batsman_runs = data[15]
    d.extra_runs = data[16]
    d.total_runs = data[17]
    d.player_dismissed = data[18]
    d.dismissal_kind = data[19]
    d.fielder = data[20]
    d.save()
    print(data)
    return

def add_match_data(data):
    m = Match()
    m.sl_no = data[0]
    m.season = int(data[1])
    m.city = data[2]
    m.team1 = data[4]
    m.team2 = data[5]
    m.toss_winner = data[6]
    m.toss_decision = data[7]
    m.result = data[8]
    m.dl_applied = int(data[9])
    m.winner = data[10]
    m.win_by_run = int(data[11])
    m.win_by_wicket = int(data[12])
    m.player_of_match = data[13]
    m.venue = data[14]
    m.umpire1 = data[15]
    m.umpire2 = data[16]
    m.umpire3 = data[17]
    print(data)
    m.save()
    return

@click.command()
def import_data():
    delivery_wb = openpyxl.load_workbook('deliveries.xlsx')
    delivery_ws = delivery_wb['Worksheet']
    row_num = 1
    for row in delivery_ws.rows:
        if row_num == 1:
            row_num += 1
            continue
        delivery_data = []
        for cell in row:
            delivery_data.append(str(cell.value))
        add_delivery_data(delivery_data)
    # match_wb = openpyxl.load_workbook('matches.xlsx')
    # match_ws = match_wb['Worksheet']
    # row_num = 1
    # for row in match_ws.rows:
    #     if row_num == 1:
    #         row_num += 1
    #         continue
    #     match_data = []
    #     for cell in row:
    #         match_data.append(str(cell.value))
    #     add_match_data(match_data)

if __name__ == '__main__':
    import_data()