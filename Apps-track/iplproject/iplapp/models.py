from django.db import models
# Create your models here.

YEAR_CHOICES=[]
for r in range(2008, 2019):
    YEAR_CHOICES.append((r, r))


class Match(models.Model):
    sl_no = models.IntegerField(default=0)
    season = models.IntegerField('season', choices=YEAR_CHOICES, default=2019)
    city = models.CharField(max_length=100)
    team1 = models.CharField(max_length=100)
    team2 = models.CharField(max_length=100)
    toss_winner = models.CharField(max_length=100)
    toss_decision = models.CharField(max_length=100)
    result = models.CharField(max_length=100)
    dl_applied = models.BooleanField(default=0)
    winner = models.CharField(max_length=100)
    win_by_run = models.IntegerField(default=0)
    win_by_wicket = models.IntegerField(default=0)
    player_of_match = models.CharField(max_length=100)
    venue = models.CharField(max_length=100)
    umpire1 = models.CharField(max_length=100)
    umpire2 = models.CharField(max_length=100)
    umpire3 = models.CharField(max_length=100)

    def __str__(self):
        return self.season

class Deliveries(models.Model):
    match_id = models.IntegerField()
    inning = models.IntegerField()
    batting_team = models.CharField(max_length=100)
    bowling_team = models.CharField(max_length=100)
    over = models.IntegerField()
    ball = models.IntegerField()
    batsman = models.CharField(max_length=100)
    non_striker = models.CharField(max_length=100)
    bowler = models.CharField(max_length=100)
    is_super_over = models.BooleanField()
    wide_runs = models.IntegerField()
    bye_runs = models.IntegerField()
    legbye_runs = models.IntegerField()
    noball_runs = models.IntegerField()
    penalty_runs = models.IntegerField()
    batsman_runs = models.IntegerField()
    extra_runs = models.IntegerField()
    total_runs = models.IntegerField()
    player_dismissed = models.CharField(max_length=100)
    dismissal_kind = models.CharField(max_length=100)
    fielder = models.CharField(max_length=100)

    def __str__(self):
        return self.match_id