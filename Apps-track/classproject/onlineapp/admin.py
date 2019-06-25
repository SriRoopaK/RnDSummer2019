from django.contrib import admin

# Register your models here.
from .models import College
from .models import Student
from .models import MockTest1
from .models import Teacher
admin.site.register(College)
admin.site.register(Student)
admin.site.register(MockTest1)
admin.site.register(Teacher)

