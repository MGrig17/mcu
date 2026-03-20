import time # импортировать модули времени и последовательного порта
import serial
import matplotlib.pyplot as plt

def read_value(ser):
	while True:
		try:
			line = ser.readline().decode('ascii')
			v, t = map(float, line.split())
			return v, t
		except ValueError:
			continue

def main(): 
    ser = serial.Serial(port='COM9', baudrate=115200, timeout=0.0) # объект Serial для работы с последовательным портом компьютера. 
    # Укажите ВАШЕ имя порта. Таймаут обязательно задать 0

    if ser.is_open: # Добавить проверку, открылся ли порт:
        print(f"Port {ser.name} opened")
    else:
        print(f"Port {ser.name} closed")

    # Создать листы для хранения результатов измерений и меток времени
    measure_temperature_C = []
    measure_voltage_V = []
    measure_ts = []

    start_ts = time.time() # Зафиксировать время старта измерений

    ser.write("tm_start\n".encode('ascii'))

    # Создать блок try - finally для гарантированного закрытия последовательного порта
    try:
        while True:
            ts = time.time() - start_ts # В теле бесконечного цикла зафиксировать время измерения

            voltage_V, temp_C = read_value(ser)

            # Добавить метку времени, напряжение и температуру в листы с результатами измерений
            measure_ts.append(ts)
            measure_voltage_V.append(voltage_V)
            measure_temperature_C.append(temp_C)

            print(f'{voltage_V:.3f} V - {temp_C:.1f}C - {ts:.2f}s') # Вывести отформатированные измерения

            time.sleep(0.1) # Добавить задержку для ограничения скорости работы бесконечного цикла
            
    finally:
        ser.write("tm_stop\n".encode('ascii'))
        ser.close()
        print("Port closed")
        # откомментируй то, что ниже, когда все остальное нормально сработает (Это 3 задание пункт 3)
        # ...
        plt.subplot(2, 1, 1)
        plt.plot(measure_ts, measure_voltage_V)
        plt.title('График зависимости напряжения от времени')
        plt.xlabel('время, с')
        plt.ylabel('напряжение, В')
        
        plt.subplot(2, 1, 2)
        plt.plot(measure_ts, measure_temperature_C)
        plt.title('График зависимости температуры от времени')
        plt.xlabel('время, с')
        plt.ylabel('температура, C')
        
        plt.tight_layout()
        plt.show()
    
# В конце файла добавить вызов функции main^
if __name__ == "__main__":
    main() 
# Далее запустить скрипт с прошивкой 03-adc, убедиться, что данные считываются и выводятся в терминал: