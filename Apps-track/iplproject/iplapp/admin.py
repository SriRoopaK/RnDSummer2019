from django.contrib import admin

# Register your models here.
from .models import Match, Deliveries
admin.site.register(Match)
admin.site.register(Deliveries)

