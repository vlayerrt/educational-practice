# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


#def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    #print(f'Hi, {name}')  # Press Ctrl+F8 to toggle the breakpoint.


# Press the green button in the gutter to run the script.
#if __name__ == '__main__':
    #print_hi('PyCharm')

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
import cv2
import locale

def viewImage(image, name_of_window):
    cv2.namedWindow(name_of_window, cv2.WINDOW_NORMAL)
    cv2.imshow(name_of_window, image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

if __name__ == '__main__':
    locale.setlocale(category=locale.LC_ALL, locale="Russian")
    image_path = "./the-witcher-3-sorceress-9.jpg"
    face_cascade = cv2.CascadeClassifier("./haarcascade_frontalface_default.xml")
    image = cv2.imread(image_path)
    viewImage(image, "Исходное изображение")
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(
    gray,
    scaleFactor= 1.1,
    minNeighbors= 5,
    minSize=(50, 50)
    )
    faces_detected = "Лиц обнаружено: " + format(len(faces))
    print(faces_detected)
    # Рисуем квадраты вокруг лиц
    for (x, y, w, h) in faces:
        cv2.rectangle(image, (x, y), (x+w, y+h), (255, 255, 0), 2)
    viewImage(image,faces_detected)