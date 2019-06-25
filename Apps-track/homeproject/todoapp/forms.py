from django import forms
from todoapp.models import Todolist, Todoitem

class todolistForm(forms.Form):
    name = forms.CharField(required=True, widget=forms.TextInput(attrs={'placeholder': 'Enter list name'}))

    class Meta:
        model = Todolist
        fields = ('name', 'created')

class todoitemForm(forms.Form):
    description = forms.CharField(required=True, widget=forms.TextInput(attrs={'placeholder': 'description'}))
    duedate = forms.DateField(required=False, widget=forms.DateInput())
    completed = forms.CheckboxInput()

    listid = forms.CharField(required=True, widget=forms.TextInput(attrs={'placeholder': 'list id'}))

    class Meta:
        model = Todoitem
        fields=('description', 'duedate', 'completed', 'listid')


class LoginForm(forms.Form):
    Username = forms.CharField(required=True, widget=forms.TextInput(attrs={'placeholder': 'Enter username','class': 'input'}))
    Password = forms.CharField(required=True, widget = forms.PasswordInput(attrs={'placeholder': 'Password', 'class': 'input'}))


class SignupForm(forms.Form):
    Firstname = forms.CharField(required=True, widget=forms.TextInput(attrs={'placeholder': 'Enter firstname'}))
    Lastname = forms.CharField(required=True, widget=forms.TextInput(attrs={'placeholder': 'Enter lastname'}))
    Username = forms.CharField(required=True, widget=forms.TextInput(attrs={'placeholder': 'Username'}))
    Password = forms.CharField(required=True, widget=forms.PasswordInput(attrs={'placeholder': 'Password'}))