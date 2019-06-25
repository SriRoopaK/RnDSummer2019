from django.db import models

# Create your models here.
class Todolist(models.Model):

    name = models.CharField(max_length=50)
    created = models.DateField(auto_now_add=True)

    def __str__(self):
        return self.name

class Todoitem(models.Model):

    description = models.CharField(max_length=600)
    due_date = models.DateField(null=True, blank=True)
    completed = models.BooleanField()

    list_id = models.ForeignKey(Todolist, on_delete=models.CASCADE)

    def __str__(self):
        return self.description

