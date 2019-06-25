#from django.views import View
# from django.shortcuts import render
# from django import forms
#
 #class CollegeView(View):
#     def get(self, request, *args, **kwargs):
#         if kwargs:
#             acronym = kwargs['acronym']
#             students = MockTest1.objects.values('student__id', 'student__name', 'total').filter(student__college__acronym=acronym)
#             return render(
#                 request,
#                 template_name="onlineapp/get_students_data.html",
#                 context={
#                     'coll': students,
#                     'title': 'Students from '+str(*College.objects.values_list('name').get(acronym=kwargs['acronym'])),
#                 }
#             )
#         college = College.objects.all()
#         return render(
#             request,
#             template_name="onlineapp/get_colleges_data.html",
#             context={
#                 'coll': college,
#                 'title': 'All college | OnlineApp',
#             }
#         )
from onlineapp.models import *
from onlineapp.forms import CollegeForm, StudentForm, MockTest1Form
from django.views import View
from django.shortcuts import render, get_object_or_404, reverse
from django.http import HttpResponseRedirect


class CollegeView(View):
    def get(self, request, *args, **kwargs):

        if self.request.path == reverse('add_college'):
                form = CollegeForm()
                return render(request, 'onlineapp/add_college.html', {
                    'form': form
                })
        if kwargs:
            if self.request.path == reverse('delete_college', kwargs={'college_acronym': kwargs['college_acronym']}):
                MockTest1.objects.filter(student__college__acronym=kwargs['college_acronym']).delete()
                Student.objects.filter(college__acronym=kwargs['college_acronym']).delete()
                College.objects.filter(acronym=kwargs['college_acronym']).delete()
                return HttpResponseRedirect('/colleges/')

            acronym = kwargs['college_acronym']
            students = MockTest1.objects.values('student__id', 'student__name', 'total').filter(student__college__acronym=acronym)
            return render(
                request,
                template_name="onlineapp/get_students_data.html",
                context={
                    'coll': students,
                    'college': kwargs['college_acronym']
                }
            )
        college = College.objects.all()
        return render(
            request,
            template_name="onlineapp/get_colleges_data.html",
            context={
                'coll'   : college,
            }
        )

    def post(self, request, *args, **kwargs):
        if kwargs:
            student_form = StudentForm(request.POST)
            mocktest1_form = MockTest1Form(request.POST)

            if student_form.is_valid() and mocktest1_form.is_valid():
                student_form.save(commit=True)
                mocktest1_form = mocktest1_form.save(commit=False)
                mocktest1_form.total = mocktest1_form.problem1 + mocktest1_form.problem2 + mocktest1_form.problem3 + mocktest1_form.problem4
                mocktest1_form.student = Student.objects.get(db_folder=request.POST['db_folder'])
                mocktest1_form.save()

            return HttpResponseRedirect('/colleges/{0}/'.format(kwargs['college_acronym']))

        form = CollegeForm(request.POST)

        if form.is_valid():
            form.save(commit=True)

        return HttpResponseRedirect('/colleges/')


class StudentView(View):
     def get(self, request, *args, **kwargs):
         if self.request.path == reverse('add_student', kwargs={'college_acronym': kwargs['college_acronym']}):
             student_form = StudentForm()
             student_form.fields['college'].initial = College.objects.get(acronym=kwargs['college_acronym'])

             mocktest1_form = MockTest1Form()

             return render(request, 'onlineapp/add_student.html', {
                 'student_form': student_form,
                 'mocktest1_form': mocktest1_form,
                 'college_acronym': kwargs['college_acronym']
             })

         if self.request.path == reverse('delete_student', kwargs={'college_acronym': kwargs['college_acronym']}):
             MockTest1.objects.filter(student__college__acronym=kwargs['college_acronym']).delete()
             Student.objects.filter(college__acronym=kwargs['acronym']).delete()
             return HttpResponseRedirect('/colleges/{0}/'.format(kwargs['college_acronym']))

     def post(self, request, *args, **kwargs):
          form = StudentForm(request.POST)

          if form.is_valid():
               form.save(commit=True)

          return HttpResponseRedirect('/colleges/{0}/'.format(kwargs['college_acronym']))