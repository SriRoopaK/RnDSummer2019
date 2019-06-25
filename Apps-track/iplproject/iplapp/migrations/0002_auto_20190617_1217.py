# Generated by Django 2.2.1 on 2019-06-17 06:47

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('iplapp', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='match',
            name='sl_no',
            field=models.IntegerField(default=0),
        ),
        migrations.AlterField(
            model_name='match',
            name='dl_applied',
            field=models.BooleanField(default=0),
        ),
        migrations.AlterField(
            model_name='match',
            name='win_by_run',
            field=models.IntegerField(default=0),
        ),
        migrations.AlterField(
            model_name='match',
            name='win_by_wicket',
            field=models.IntegerField(default=0),
        ),
    ]
