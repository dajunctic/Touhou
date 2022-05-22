@COPYRIGHT 2022 - DAZU DAZU GAMER

Thành viên:
	Vũ Quý Đạt
	Phạm Lê Minh

Game được lấy ý tưởng từ game gốc cũng tên là Touhou
Link tham khảo: https://www.youtube.com/watch?v=-s3e2loaRUY&t=53s


Có thể chạy game bằng file exe hoặc gõ các câu lệnh sau lần lượt trên terminal hoặc command prompt
	g++ -Iinclude -Iinclude/sdl -Iinclude/headers -Llib -o Touhou src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
	./Touhou.exe

Về phân công công việc

* Về đồ họa
	Phạm Lê Minh: phụ trách tìm các animation trên các open và free source
	Vũ Quý Đạt: Các ảnh ở các chức nănng khác và photoshop, xử lí toàn bộ ảnh cho phù hợp

* Về mã nguồn

	Vũ Quý Đạt:
		- Xây dựng project rỗng, tách sẵn các folder cho các mục đích riêng
		- Xây dựng các thư viện đồ họa cần sử dụng SDL ban đầu:
			+ Game, GameImage, GameTime, GameMusic, GameText
		- Xây dựng một số chức năng và một số phần trong màn chơi như:
			+  GameMenu, GameEnd, MusicList, GameStage(30%), GameStory(40%), Character
	Phạm Lê Minh
		- Xây dựng thư viện hỗ trợ màn chơi
			+ GamePhysics
		- Xây dựng các phần cho màn chơi
			+ Enemy, Bullet, GameStage(70%), GameStory(60%)

Tổng quan:
	Game có sử dụng toàn bộ các yêu cầu của bài tập lớn như:
		Cấu trúc/Lớp - Dùng để tách các thư viện
		Biến/kiểu dữ liệu/con trỏ - Dùng trong các hàm trong thư viện
		Danh sách/Danh sách liên kết/Nhiều đối tượng - Sử dụng trong thư viện Music List có 
		Thao tác với file - Sử dụng trong thư viện Music List và Game Story
		Chia tách chương trình - Có tách các thư viện một cách rõ ràng nhất có thể

	Dựa theo số lượng dòng code và một số yếu tố khác như thời gian đầu tư vào bài tập lớn, lên ý tưởng v.v
	- Vũ Quý Đạt hoàn thành trung bình 60%
	- Lê Vũ Minh hoàn thành trung bình 40% 
	