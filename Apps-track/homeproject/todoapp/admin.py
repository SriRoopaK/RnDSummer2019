from django.contrib import admin

# Register your models here.
from .models import Todoitem
from .models import Todolist
admin.site.register(Todoitem)
admin.site.register(Todolist)