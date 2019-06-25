from todoapp.forms import LoginForm,SignupForm
from django.views import View
from django.shortcuts import render, get_object_or_404, reverse, redirect
from django.http import HttpResponseRedirect, HttpResponse
from django.contrib.auth import login, logout, authenticate
from django.contrib.auth.models import User
from todoapp.models import Todolist, Todoitem
from todoapp.forms import todolistForm
class lists(View):
    def get(self, request):
        lists = Todolist.objects.all()
        return render(request, 'todoapp/lists.html', {'lists': lists})


class items(View):
    def get(self, request, listid):
        items_list = Todoitem.objects.filter(list_id=listid)
        return render(request, 'todoapp/items.html', {'items':items_list})

class addList(View):
    def get(self, request):
        form = todolistForm()
        return render(request, 'todoapp/addList.html', {'form':form})

    def post(self, request):
        new_list = todolistForm(request.POST)
        if new_list.is_valid():
            new_list.save(commit=True)
        lists = Todolist.objects.all()
        return render(request, 'todoapp/lists.html', {'lists': lists})