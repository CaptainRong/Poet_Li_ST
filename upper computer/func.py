import time
import serial
import serial.tools.list_ports
from cnocr import CnOcr
import cv2

def detect_serial():
    # 获取所有串口设备实例。
    # 如果没找到串口设备，则输出：“无串口设备。”
    # 如果找到串口设备，则依次输出每个设备对应的串口号和描述信息。
    ports_list = list(serial.tools.list_ports.comports())
    if len(ports_list) <= 0:
        print("无串口设备。")
    else:
        print("可用的串口设备如下：")
        for comport in ports_list:
            print(list(comport)[0], list(comport)[1])
    return list(comport)


def connect_serial(port):
    '''
    port - 串口设备名或 None。
    baudrate - 波特率，可以是50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 500000, 576000, 921600, 1000000, 1152000, 1500000, 2000000, 2500000, 3000000, 3500000, 4000000。
    bytesize - 数据位，可取值为：FIVEBITS, SIXBITS, SEVENBITS, EIGHTBITS。
    parity - 校验位，可取值为：PARITY_NONE, PARITY_EVEN, PARITY_ODD, PARITY_MARK, PARITY_SPACE。
    stopbits - 停止位，可取值为：STOPBITS_ONE, STOPBITS_ONE_POINT_FIVE, STOPBITS_TOW。
    xonxoff - 软件流控，可取值为 True, False。
    rtscts - 硬件（RTS/CTS）流控，可取值为 True, False。
    dsr/dtr - 硬件（DSR/DTR）流控，可取值为 True, False。
    timeout - 读超时时间，可取值为 None, 0 或者其他具体数值（支持小数）。当设置为 None 时，表示阻塞式读取，一直读到期望的所有数据才返回；当设置为 0 时，表示非阻塞式读取，无论读取到多少数据都立即返回；当设置为其他数值时，表示设置具体的超时时间（以秒为单位），如果在该时间内没有读取到所有数据，则直接返回。
    write_timeout: 写超时时间，可取值为 None, 0 或者其他具体数值（支持小数）。参数值起到的效果参考 timeout 参数。
    '''
    ser = serial.Serial(port, 115200, timeout=0.2)  # 打开COM17，将波特率配置为115200，其余参数使用默认值
    if ser.isOpen():  # 判断串口是否成功打开
        print("打开串口成功。")
    else:
        print("打开串口失败。")
    return ser


def send(ser, text):
    write_len = ser.write(text.encode('utf-8'))
    print(f"DEBUG:串口发出{write_len}个字节: {text}")


def figure_check(cap, ser, answer=None, delay=1):
    if not answer:
        current = detect(cap)
        print(f"DEBUG:Detect as {current}")
        if current == 'A':
            figure_check(cap, ser, '20221071473')
        elif current == 'B':
            figure_check(cap, ser, '20221071019')
        elif current == 'C':
            figure_check(cap, ser, '20221071345')
    else:
        for i in range(len(answer)):
            while detect(cap) != answer[i]:
                print(f"DEBUG:Detect as {detect(cap)}, as it should be {answer[i]}")
                time.sleep(delay)
            if i+1 != len(answer):
                send(ser, f"0x0{answer[i+1]}")
            print(f"check finished:{answer[i]}")
            time.sleep(delay)

        print("Check Done!")
        send(ser, answer)


ocr = CnOcr(det_model_name='en_PP-OCRv3_det', rec_model_name='en_PP-OCRv3', cand_alphabet=["A", "B", "C", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"])
def detect(cap):
    ret, img = cap.read()
    cv2.imshow("camera", img)
    result = ocr.ocr_for_single_line(img)
    return result['text']


if __name__ == '__main__':
    ports = detect_serial()
    ser = connect_serial(ports[0])
    send(ser, "A55A20221071473A5A5")
