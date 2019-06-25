from onlineapp.forms import LoginForm,SignupForm
from django.views import View
from django.shortcuts import render, get_object_or_404, reverse, redirect
from django.http import HttpResponseRedirect
from django.contrib.auth import login, logout, authenticate
from django.contrib.auth.models import User


def logout(request):
    logout(request)
    return redirect('/login/')


class LoginView(View):
    def get(self, request):
        form = LoginForm()
        return render(request, 'onlineapp/login.html', {'form': form})

    def post(self, request):
        form = LoginForm(request.POST)
        if form.is_valid():
         username = form.cleaned_data['Username']
         password = form.cleaned_data['Password']
         user = authenticate(request, username=username, password=password)
         if user is not None:
            login(request, user)
            return HttpResponseRedirect('/colleges/')
         else:
            return HttpResponseRedirect('/login/')


class SignupView(View):

    def get(self, request):
        form = SignupForm()
        return render(request, 'onlineapp/signup.html', {'form':form})

    def post(self, request):
        form = SignupForm(request.POST)
        if form.is_valid():
            user = User.objects.create_user(**form.cleaned_data)
            user.save()

        if user is not None:
            login(request, user)
            return redirect('/colleges/')

