"""classproject URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.conf.urls import url
from django.contrib import admin

from django.conf import settings
from django.urls import include, path
from rest_framework.authtoken.views import obtain_auth_token
from onlineapp.views import CollegeView,StudentView,LoginView,SignupView
from onlineapp.views import RestStudentsView, RestStudentView, LoginView, SignupView
from onlineapp import rest

urlpatterns = [
    path('admin/', admin.site.urls),
    # path('hello/', views.hello_world),
    # path('html_hello/', views.html_hello),
    path('colleges/', CollegeView.as_view(), name='colleges_html'),
    path('colleges/add-college/', CollegeView.as_view(), name='add_college'),
    path('colleges/<str:college_acronym>/', CollegeView.as_view(), name='students_html'),
    path('colleges/<str:college_acronym>/add-student/', StudentView.as_view(), name='add_student'),
    path('colleges/<str:college_acronym>/delete-college/', CollegeView.as_view(), name='delete_college'),
    path('colleges/<str:college_acronym>/delete-student/', StudentView.as_view(), name='delete_student'),


    path('login/', LoginView.as_view(), name='login'),
    path('signup/', SignupView.as_view(), name='signup'),


    path('api/v1/colleges/', rest.get_colleges),
    path('api/v1/colleges/<int:cid>/', rest.get_college_id),
    path('api/v2/colleges/<int:cid>/students/', RestStudentsView.as_view(), name='rest_students'),
    path('api/v2/colleges/<int:cid>/students/<int:sid>', RestStudentView.as_view(), name='rest_student'),
    path('api-token-auth/', obtain_auth_token, name='api_token_auth'),
]
if settings.DEBUG:
    import debug_toolbar
    urlpatterns = [
        path('__debug__/', include(debug_toolbar.urls)),
    ] + urlpatterns

