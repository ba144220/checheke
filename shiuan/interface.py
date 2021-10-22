import BT
import score

class interface:
    def __init__(self):
        print("")
        print("Arduino Bluetooth Connect Program.")
        print("")
        self.ser = BT.bluetooth()
        port = input("PC bluetooth port name: ")
        
        while(not self.ser.do_connect(port)):
            if(port == "quit"):
                self.ser.disconnect()
                quit()
            port = input("PC bluetooth port name: ")



    def get_UID(self):
        return self.ser.SerialReadByte()

    def send_action(self,cmd):
        # TODO : send the action to car
        self.ser.SerialWrite(cmd)
        return

    def end_process(self):
        self.ser.SerialWrite('e')
        self.ser.disconnect()

    def input_action(self):
        cmd = input('next cmd:')
        if cmd == 'quit':
            self.ser.disconnect()
            sys.exit()
            return
        self.send_action(cmd)

    def action_to_send(self, direction):
        if direction == 1:
            self.send_action('w')
        elif direction ==2:
            self.send_action('s')
        elif direction ==3:
            self.send_action('d')
        elif direction ==4:
            self.send_action('a')


def main():
    interf = interface()
    point = score.Scoreboard("data/UID.csv", "DaoDaoDao", 1)
    while(True):
        receiveMsg = interf.ser.SerialReadUID()
        print(receiveMsg)
        point.add_UID(receiveMsg)
        print('Score:', point.getCurrentScore())

if __name__ == '__main__':
    main()
