import pyautogui
from time import sleep

def main():
    # 浏览器位置
    browser_file = './browser.png'
    refesh_buttom_file = "./refresh.png" 
    pyautogui.hotkey("win")
    sleep(1)

    print(pyautogui.locateOnScreen(browser_file))

    refesh_buttom = pyautogui.locateOnScreen(refesh_buttom_file)
    if(None != refesh_buttom):
        pyautogui.click(refesh_buttom)

    while(1):
        pyautogui.scroll(30)
        sleep(1)
    pass

def send_fun():
    send_buttom_file = "send.png"
    emj_buttom_file = "./emj.png"
    my_emj_file = "./my_emj.png"
    send_emj_file = "./send_emj.png"
    while(1):
        emj_buttom = pyautogui.locateOnScreen(emj_buttom_file)
        if(None != emj_buttom):
            pyautogui.click(emj_buttom)
            print("emj buttom pos: " + str(emj_buttom))

        my_emj_buttom = pyautogui.locateOnScreen(my_emj_file)
        if(None != my_emj_buttom):
            pyautogui.click(my_emj_buttom)
            print("myemj buttom pos: " + str(my_emj_buttom))

        send_emj_buttom = pyautogui.locateOnScreen(send_emj_file)
        if(None != send_emj_buttom):
            pyautogui.click(send_emj_buttom)
            print("myemj buttom pos: " + str(send_emj_buttom))

        send_buttom = pyautogui.locateOnScreen(send_buttom_file)
        if(None != send_buttom):
            #pyautogui.click(send_buttom)
            print("send buttom pos: " + str(send_buttom))
        sleep(1)

if __name__ == "__main__":
    #send_fun()
    main()