import os
import django


os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'classproject.settings')
django.setup()

from onlineapp.models import College

def db_retrieve():
    c=College.objects.all()
    print(c)

if __name__=='__main__':
    db_retrieve()

