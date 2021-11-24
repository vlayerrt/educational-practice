# import libraries
import face_recognition
import cv2
import os
from google.colab.patches import cv2_imshow
 
input_movie=cv2.VideoCapture("video_2.mp4")
lenght=1
width=1080
height=720
known_faces=[]
known_names=[]
fourcc=cv2.VideoWriter_fourcc(*'XVID')
output_movie=cv2.VideoWriter('output.mp4',fourcc,29.97,(width,height),True)
path_photos="photos/"
output_movie


def load_movie(path_input,path_output):
  global input_movie, lenght, height, width,output_movie
  input_movie = cv2.VideoCapture("video_2.mp4")
  lenght = int(input_movie.get(cv2.CAP_PROP_FRAME_COUNT))
  height = int(input_movie.get(cv2.CAP_PROP_FRAME_HEIGHT))
  width = int(input_movie.get(cv2.CAP_PROP_FRAME_WIDTH))
  fourcc = cv2.VideoWriter_fourcc(*'XVID')
  output_movie = cv2.VideoWriter('output.mp4', fourcc,29.97,(width,height),True)

def learn_faces():
  photos=os.listdir(path_photos)
  for photo in photos:

    try:
       image=face_recognition.load_image_file(path_photos+photo)
       face_encoding=face_recognition.face_encodings(image)[0]
       known_faces.append(face_encoding)
       known_names.append(photo.rsplit(".",1 ) [0 ])
    except:
         print("Photo "+photo+" not encoding")

face_locations= []
face_encodings= []
face_names= []
frame_number= 0
load_movie("video_2.mp4","output.mp4")
learn_faces()

for i in range(len(known_faces)):
  print(known_names[i])
print(lenght)

while True:
    ret,frame=input_movie.read()
    frame_number +=1
    if not ret:
        break
    rgb_frame = frame[:,:,::-1]

    face_locations=face_recognition.face_locations(rgb_frame)
    face_encodings=face_recognition.face_encodings(rgb_frame,face_locations)
    face_names=[]
    for face_encoding in face_encodings:
      match = face_recognition.compare_faces(known_faces, face_encoding,tolerance=0.50)
      name = None
      for m in range(len(match)):
        if match[m]:
          name = known_names[m]
          print(name)
          face_names.append(name)
          break

    for (top,right,bottom,left), name in zip(face_locations, face_names):
        if not name:
            continue
        cv2.rectangle(frame,(left,top),(right,bottom),(0, 0, 255), 2)

        cv2.rectangle(frame,(left,bottom-25),(right,bottom), (0,0,255), cv2.FILLED)
        font =cv2.FONT_HERSHEY_DUPLEX
        cv2.putText(frame,name, (left + 6, bottom - 6), font, 0.5,(255,255,255), 1)

    print("Writing frame {} / {}".format(frame_number,lenght))
    output_movie.write(frame)


output_movie.release()
cv2.destroyAllWindows()
