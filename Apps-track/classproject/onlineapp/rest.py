from django.shortcuts import render
from django.http import HttpResponse
from rest_framework.decorators import api_view,permission_classes
from rest_framework.response import Response
from rest_framework import status
from .models import *
from onlineapp.serializers import CollegeSerializer
from rest_framework.permissions import IsAuthenticated

@api_view(['GET', 'POST'])
@permission_classes((IsAuthenticated,))
def get_colleges(request):

    if request.method == 'GET':
        colleges = College.objects.all()
        serializer = CollegeSerializer(colleges, many=True)
        return Response(serializer.data, status=status.HTTP_200_OK)

    if request.method == 'POST':
        serializer = CollegeSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.data, status=status.HTTP_400_BAD_REQUEST)


@api_view(['GET', 'DELETE', 'PUT'])
def get_college_id(request, cid):
    if request.method == 'GET':
        college = College.objects.get(id=cid)
        serializer = CollegeSerializer(college)
        return Response(serializer.data, status=status.HTTP_200_OK)

    if request.method == 'DELETE':
        College.objects.get(id=cid).delete()
        return Response(status=status.HTTP_202_ACCEPTED)

    if request.method == 'PUT':
        college=College.objects.get(id=cid)
        serializer = CollegeSerializer(college, data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
