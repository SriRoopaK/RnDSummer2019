from todoapp.forms import LoginForm,SignupForm
from django.views import View
from django.shortcuts import render, get_object_or_404, reverse, redirect
from django.http import HttpResponseRedirect, HttpResponse
from django.contrib.auth import login, logout, authenticate
from django.contrib.auth.models import User
from todoapp.models import Todolist, Todoitem

class LoginView(View):

    def get(self, request):
        form = LoginForm()
        return render(request, 'todoapp/login.html', {'form': form})

    def post(self, request):
        form = LoginForm(request.POST)
        if form.is_valid():
          username = form.cleaned_data['Username']
          password = form.cleaned_data['Password']
          user = authenticate(request, username=username, password=password)
          if user is not None:
            login(request, user)
            return HttpResponseRedirect('/lists/')
          return HttpResponseRedirect('/login/')


class SignupView(View):

    def get(self, request):
        form = SignupForm()
        return render(request, 'todoapp/signup.html', {'form': form})

    def post(self, request):
        form = SignupForm(request.POST)
        if form.is_valid():
            user = User.objects.create_user(form.cleaned_data['Username'], form.cleaned_data['Password'])
            user.save()

        if user is not None:
            login(request, user)
            return redirect('/display/')


class display(View):
    def get(self,request):
        lists = Todolist.objects.all()
        response = "<html><body><table border='1px'>"
        for list in lists:
            response += "<tr><td>"
            response += list.name
            response += "</td></tr>"
        response += "</table></body></html>"
        return HttpResponse(response)