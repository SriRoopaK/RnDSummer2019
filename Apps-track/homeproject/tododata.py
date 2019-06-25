import click
import django
import os
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'homeproject.settings')
django.setup()

from todoapp.models import Todolist,Todoitem

@click.command()
def tododata():

    for list_num in range(5):
        list_record = Todolist(name="todolist"+str(list_num+1))
        list_record.save()
        for item_num in range(5):
            list_item = Todoitem(description="list"+str(list_num+1)+"item"+str(item_num+1), completed=0, list_id=Todolist.objects.get(id=list_num+1))
            list_item.save()


if __name__ == '__main__':
    tododata()