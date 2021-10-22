from time import sleep
import serial
import struct
# these codes are for bluetooth

class bluetooth:
    def __init__(self):
        self.ser = serial.Serial()

    def do_connect(self,port):
        self.ser.close()
        print("Connecting...")
        self.ser = serial.Serial(port,9600)
        while self.ser.is_open:
            print("connect success")
            print("")
            return True
        #except:
        #   pass
            #except serial.serialutil.SerialException:
                #print("fail to connect")
                #print("")
                #return False
        return True


    def disconnect(self):
        self.ser.close()

    def SerialWrite(self,output):
        # send = 's'.encode("utf-8")
        send = output.encode("utf-16")
        self.ser.write(send)
        print(send, 'sent!')

    def waiting(self) -> bool:
        return self.ser.in_waiting
    
    def SerialReadString(self):
        # TODO: Get the information from Bluetooth. Notice that the return type should be transformed into hex.
        '''
        waiting = self.ser.in_waiting
        if waiting >= 0:
            rv = self.ser.read(1).decode("utf-8")
            return rv
        return""
        '''
        if self.waiting():
            receiveMsg = self.ser.read(size=1)
            #decodeMsg = receiveMsg.decode("utf-8")
            return receiveMsg
        return None
        
    def SerialReadUID(self):
        while not self.waiting():
            pass
        msg = self.ser.read()
        #msgdecode = msg.decode('utf-8')
        #print(msg)
        #print(msgdecode)
        id_size = int.from_bytes(msg, byteorder='big')
        #msg_str = msg.encode(encoding='gb2312')
        print(id_size)

        #id_size = int(self.ser.read())
        #id_size = 4
        UID_bytes = b''
        UID_string = ""
        for i in range(id_size):
            while not self.waiting():
                pass
            receiveMsg = self.ser.read()
            temp = int.from_bytes(receiveMsg, byteorder='big')
            print(hex(temp))
            UID_string += hex(temp).upper()[2:4]
            UID_bytes += receiveMsg
        print(UID_bytes)
        print(UID_string)
        UID = str(UID_bytes)[2:-1]
        #UID = hex(int.from_bytes(rv, byteorder='big', signed=False))
        self.ser.flushInput()
        #print(UID)
        return UID
            

    def SerialReadByte(self):
        sleep(0.05)
        id_size = self.ser.read()
        id_size = int.from_bytes(id_size, byteorder='big')
        waiting = self.ser.inWaiting()
        rv = self.ser.read(waiting)
        if(rv):
            UID = hex(int.from_bytes(rv, byteorder='big', signed=False))
            self.ser.flushInput()
            UID = str(UID)[2:]
            print(UID)
            lack = 2*id_size - len(UID)
            for i in range(lack):
                UID = '0' + UID
            UID = UID.upper()
            print(UID)
            return UID
        else:
            return 0

    def PrintString(self):
        while True:
            while not self.waiting:
                pass
            temp = self.SerialReadString()
            while temp == None:
                temp = self.SerialReadString()
                pass
            print(temp)
            return temp

def main():
   return 0

if __name__ == '__main__':
    main()
