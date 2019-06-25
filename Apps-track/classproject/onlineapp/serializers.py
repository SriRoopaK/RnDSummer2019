from rest_framework import serializers
from onlineapp.models import College,Student,MockTest1


class CollegeSerializer(serializers.ModelSerializer):
    class Meta:
        model = College
        fields = ('id', 'name', 'location', 'acronym', 'contact')


class MockTestSerializer(serializers.ModelSerializer):
    class Meta:
        model = MockTest1
        fields = ('problem1', 'problem2', 'problem3', 'problem4', 'total', 'student')


class StudentSerializer(serializers.ModelSerializer):
    mocktest1 = MockTestSerializer(many=False, read_only=False)

    class Meta:
        model = Student
        fields = ('id', 'name', 'dob', 'email', 'db_folder', 'dropped_out', 'college', 'mocktest1')

    def create(self, valid_data):
        mockmarks =valid_data.pop('mocktest1')
        student = Student.objects.create(**valid_data)
        MockTest1.objects.create(student=student, **mockmarks)
        return student

    def update(self, instance, valid_data):
        mocktest1_data = valid_data.pop('mocktest1')

        instance.name = valid_data.get('name', instance.name)
        instance.email = valid_data.get('email', instance.email)
        instance.dob = valid_data.get('dob', instance.dob)
        instance.db_folder = valid_data.get('db_folder', instance.db_folder)
        instance.dropped_out = valid_data.get('dropped_out', instance.dropped_out)
        instance.college = valid_data.get('college', instance.college)
        instance.save()

        mocktest1 = MockTest1.objects.get(student_id=instance.id)
        mocktest1.problem1 = mocktest1_data.get('problem1', mocktest1.problem1)
        mocktest1.problem2 = mocktest1_data.get('problem2', mocktest1.problem2)
        mocktest1.problem3 = mocktest1_data.get('problem3', mocktest1.problem3)
        mocktest1.problem4 = mocktest1_data.get('problem4', mocktest1.problem4)
        mocktest1.total = mocktest1_data.get('total', mocktest1.total)
        mocktest1.save()

        return instance
