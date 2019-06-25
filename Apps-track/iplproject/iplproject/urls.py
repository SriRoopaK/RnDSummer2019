"""iplproject URL Configuration

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
from django.contrib import admin
from django.urls import path
from iplapp import views
from iplapp.Authenticate import LoginView, SignupView, logout_from

urlpatterns = [
    path('admin/', admin.site.urls),

    path('login/', LoginView.as_view(), name='login'),
    path('signup/', SignupView.as_view(), name='signup'),
    path('logout/', logout_from, name='logout'),

    path('', views.home),
    path('seasons/', views.season_details),
    path('seasons/<int:year>/', views.season_details),
    path('seasons/<int:year>/match_details/<int:match_id>', views.match_report),

    path('<int:year>/points_table', views.points_table),

    path('teams/', views.teams),
    path('teams/<str:team_name>/', views.team_details),
]
