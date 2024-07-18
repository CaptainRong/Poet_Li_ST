from func import *


if __name__ == '__main__':
    ports = detect_serial()
    ser = connect_serial(ports[0])
    # 打开摄像头
    cap = cv2.VideoCapture(0)
    input("Ports and camera are connected. Press Enter to continue.")
    if not cap.isOpened():
        print("无法打开摄像头")
        exit()
    while(1):
        figure_check(cap, ser, delay=0.1)

        if cv2.waitKey(1) == ord('q'):
            break


    # 释放摄像头和关闭窗口
    cap.release()
    cv2.destroyAllWindows()
