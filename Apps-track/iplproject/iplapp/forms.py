from django import forms

class LoginForm(forms.Form):
    Username = forms.CharField(required=True, widget=forms.TextInput(attrs={'placeholder': 'Enter username', 'class': 'input'}))
    Password = forms.CharField(required=True, widget = forms.PasswordInput(attrs={'placeholder': 'Password', 'class': 'input'}))


class SignupForm(forms.Form):
    Firstname = forms.CharField(required=True, widget=forms.TextInput(attrs={'placeholder': 'Enter firstname'}))
    Lastname = forms.CharField(required=True, widget=forms.TextInput(attrs={'placeholder': 'Enter lastname'}))
    Username = forms.CharField(required=True, widget=forms.TextInput(attrs={'placeholder': 'Username'}))
    Password = forms.CharField(required=True, widget=forms.PasswordInput(attrs={'placeholder': 'Password'}))