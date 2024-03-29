# Generated by Django 2.2.1 on 2019-06-17 05:15

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Match',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('season', models.IntegerField(choices=[(2008, 2008), (2009, 2009), (2010, 2010), (2011, 2011), (2012, 2012), (2013, 2013), (2014, 2014), (2015, 2015), (2016, 2016), (2017, 2017), (2018, 2018)], default=2019, verbose_name='season')),
                ('city', models.CharField(max_length=100)),
                ('team1', models.CharField(max_length=100)),
                ('team2', models.CharField(max_length=100)),
                ('toss_winner', models.CharField(max_length=100)),
                ('toss_decision', models.CharField(max_length=100)),
                ('result', models.CharField(max_length=100)),
                ('dl_applied', models.BooleanField()),
                ('winner', models.CharField(max_length=100)),
                ('win_by_run', models.IntegerField()),
                ('win_by_wicket', models.IntegerField()),
                ('player_of_match', models.CharField(max_length=100)),
                ('venue', models.CharField(max_length=100)),
                ('umpire1', models.CharField(max_length=100)),
                ('umpire2', models.CharField(max_length=100)),
                ('umpire3', models.CharField(max_length=100)),
            ],
        ),
        migrations.CreateModel(
            name='Deliveries',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('inning', models.IntegerField()),
                ('batting_team', models.CharField(max_length=100)),
                ('bowling_team', models.CharField(max_length=100)),
                ('over', models.IntegerField()),
                ('ball', models.IntegerField()),
                ('batsman', models.CharField(max_length=100)),
                ('non_striker', models.CharField(max_length=100)),
                ('bowler', models.CharField(max_length=100)),
                ('is_super_over', models.BooleanField()),
                ('wide_runs', models.IntegerField()),
                ('bye_runs', models.IntegerField()),
                ('legbye_runs', models.IntegerField()),
                ('noball_runs', models.IntegerField()),
                ('penalty_runs', models.IntegerField()),
                ('batsman_runs', models.IntegerField()),
                ('extra_runs', models.IntegerField()),
                ('total_runs', models.IntegerField()),
                ('player_dismissed', models.CharField(max_length=100)),
                ('dismissal_kind', models.CharField(max_length=100)),
                ('fielder', models.CharField(max_length=100)),
                ('match', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='iplapp.Match')),
            ],
        ),
    ]
