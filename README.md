# @COPYRIGHT 2022 - DAJU STUDIO

**Thành viên:**
- Vũ Quý Đạt
- Phạm Lê Minh

Game được lấy ý tưởng từ game gốc cũng tên là Touhou.

#### **Video tham khảo:** 

 [![1](https://img.youtube.com/vi/-s3e2loaRUY/default.jpg)](https://www.youtube.com/watch?v=-s3e2loaRUY&t=53s)

#### **Video sản phẩm:** 

[![2](https://img.youtube.com/vi/FLT3CSHpV1E/default.jpg)](https://youtu.be/FLT3CSHpV1E)


Mọi người có thể chạy game bằng file exe hoặc gõ các câu lệnh sau lần lượt trên terminal hoặc command prompt nếu máy có cài đặt **MINGW**.
```makefile
g++ -Iinclude -Iinclude/sdl -Iinclude/headers -Llib -o Touhou src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
./Touhou.exe
```
