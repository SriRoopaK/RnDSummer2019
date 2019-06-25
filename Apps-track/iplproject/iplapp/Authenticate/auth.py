from iplapp.forms import LoginForm,SignupForm
from django.views import View
from django.shortcuts import render, get_object_or_404, reverse, redirect
from django.http import HttpResponseRedirect
from django.contrib.auth import login, logout, authenticate
from django.contrib.auth.models import User

def logout_from(request):
    logout(request)
    return redirect('/')

class LoginView(View):

    def get(self, request):
        form = LoginForm()
        return render(request, 'iplapp/login.html', {'form': form})

    def post(self, request):
        form = LoginForm(request.POST)
        if form.is_valid():
            username = form.cleaned_data['Username']
            password = form.cleaned_data['Password']
            user = authenticate(request, username=username, password=password)
            if user is not None:
                login(request, user)
                return HttpResponseRedirect('/')
            return HttpResponseRedirect('/login/')


class SignupView(View):

    def get(self, request):
        form = SignupForm()
        return render(request, 'iplapp/signup.html', {'form': form})

    def post(self, request):
        form = SignupForm(request.POST)
        if form.is_valid():
            user = User.objects.create_user(username=form.cleaned_data['Username'], password=form.cleaned_data['Password'])
            user.save()

            if user is not None:
                login(request, user)
                return redirect('/')
