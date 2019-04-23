## 15.351 Project

Based on tensorflow pose estimation

How information is stored:

tf-pose-estimation returns an array of this type

The tuple (a,b) example: (0.15, 0.29) represents the position of the body part, 0.15 represents 0.15 down from the top and 0.29 is 0.29 of the image from the left

[BodyPart:0-(0.15, 0.29) score=0.81 BodyPart:1-(0.14, 0.39) score=0.76 BodyPart:2-(0.08, 0.38) score=0.78 BodyPart:3-(0.04, 0.46) score=0.52 BodyPart:4-(0.09, 0.47) score=0.43 BodyPart:5-(0.19, 0.40) score=0.72 BodyPart:6-(0.20, 0.48) score=0.42 BodyPart:7-(0.13, 0.48) score=0.15 BodyPart:8-(0.06, 0.57) score=0.30 BodyPart:11-(0.12, 0.58) score=0.26 BodyPart:14-(0.14, 0.27) score=0.89 BodyPart:15-(0.17, 0.28) score=0.69 BodyPart:16-(0.12, 0.27) score=0.25 BodyPart:17-(0.19, 0.30) score=0.69, BodyPart:0-(0.33, 0.33) score=0.38 BodyPart:1-(0.31, 0.41) score=0.40 BodyPart:2-(0.26, 0.41) score=0.45 BodyPart:3-(0.23, 0.49) score=0.39 BodyPart:5-(0.37, 0.43) score=0.33 BodyPart:6-(0.37, 0.50) score=0.09 BodyPart:7-(0.37, 0.42) score=0.23 BodyPart:8-(0.27, 0.55) score=0.08 BodyPart:11-(0.33, 0.57) score=0.14 BodyPart:14-(0.33, 0.30) score=0.55 BodyPart:15-(0.35, 0.32) score=0.59 BodyPart:16-(0.25, 0.34) score=0.72 BodyPart:17-(0.37, 0.35) score=0.27, BodyPart:0-(0.89, 0.33) score=0.34 BodyPart:1-(0.89, 0.39) score=0.24 BodyPart:2-(0.87, 0.39) score=0.24 BodyPart:5-(0.92, 0.39) score=0.20 BodyPart:14-(0.88, 0.32) score=0.30 BodyPart:15-(0.89, 0.32) score=0.34 BodyPart:16-(0.88, 0.33) score=0.18 BodyPart:17-(0.90, 0.33) score=0.16, BodyPart:0-(0.27, 0.34) score=0.67 BodyPart:1-(0.26, 0.39) score=0.50 BodyPart:5-(0.28, 0.40) score=0.53 BodyPart:14-(0.26, 0.33) score=0.67 BodyPart:15-(0.27, 0.34) score=0.70 BodyPart:16-(0.25, 0.34) score=0.72 BodyPart:17-(0.28, 0.34) score=0.37, BodyPart:0-(0.46, 0.33) score=0.70 BodyPart:1-(0.55, 0.60) score=0.13 BodyPart:5-(0.71, 0.60) score=0.19 BodyPart:14-(0.41, 0.27) score=0.82 BodyPart:15-(0.51, 0.25) score=0.86 BodyPart:17-(0.60, 0.29) score=0.69]

Nose = 0
Neck = 1
RShoulder = 2
RElbow = 3
RWrist = 4
LShoulder = 5
LElbow = 6
LWrist = 7
RHip = 8
RKnee = 9
RAnkle = 10
LHip = 11
LKnee = 12
LAnkle = 13
REye = 14
LEye = 15
REar = 16
LEar = 17
Background = 18
