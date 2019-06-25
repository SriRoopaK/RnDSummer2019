from django.views import View
from onlineapp.models import College,Student,MockTest1
from onlineapp.serializers import StudentSerializer
from rest_framework import status
from rest_framework.response import Response
from rest_framework.views import APIView
from rest_framework.permissions import IsAuthenticated

class RestStudentsView(APIView):
    permission_classes = (IsAuthenticated,)
    def get(self, request, cid):
        students = Student.objects.filter(college=cid)
        serializer = StudentSerializer(students, many=True)
        return Response(serializer.data, status=status.HTTP_200_OK)

    def post(self, request, *arg, **kwargs):
        try:
            request.data['college'] = kwargs['cid']
        except College.DoesNotExist:
            return Response(status=404)
        serializer = StudentSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        else:
            data = {
                'error': True,
                'errors': serializer.errors
            }
            return Response(data)


class RestStudentView(APIView):
    def get(self,request,cid,sid):
        student = Student.objects.get(id=sid)
        serializer = StudentSerializer(student)
        return Response(serializer.data, status=status.HTTP_200_OK)

    def delete(self, request, cid, sid):
        Student.objects.get(id=sid).delete()
        return Response(status=status.HTTP_200_OK)

    def put(self, request, *args, **kwargs):
        try:
            student = Student.objects.get(pk=kwargs['sid'])
            request.data['college']=kwargs['cid']
        except College.DoesNotExist:
            return Response(status=404)
        data = request.data
        serializer = StudentSerializer(instance=student, data=data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        else:
            return Response(serializer.errors, status=400)
