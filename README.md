![image](https://github.com/user-attachments/assets/71b126ba-b3f5-4f6a-ba99-49af12ac5af5)
# Jellyfish_game

**Hành trình về nhà của sứa con**

**Vid Demo**[
-	https://drive.google.com/file/d/1m8xQaVCj5kD8mEtw95cVEU6RK2bLbaXR/view?usp=sharing

**1. Giới thiệu:**

   Jellyfish Game là thử thách tìm đường của 1 chú Sứa con bị lạc giữa vùng biển xa xôi. Sứa phải vượt qua các trở ngại trên đường và tiêu diệt chúng, ăn bánh trên đường để lớn hơn, diện mạo đẹp hơn. Cuối cùng, Sứa phải gặp Boss cuối trước cửa về nhà, chỉ cần tiêu diệt đươc con Boss này, chú Sứa sẽ hoàn thành nhiệm vụ và về nhà thành công.
   _________________
**2. Tiến trình:**

    - THAM KHẢO TỪ YOUTOBE : Học Lập Trình Game C++ SDL Giới Thiệu Phần 2:
    https://www.youtube.com/watch?v=k6iKwWc4hck&list=PLR7NDiX0QsfTIEQUeYCfc2MyCquX0ig9V&index=3
  + Thử chạy ảnh image cho Background.cpp
  + Main, Common, BaseObjects : Tạo kiến trúc cho Project Game (ở bên ngoài không trong tệp nào cả)
  + Kỹ thuật Tile map thử nghiệm cho game (trong tệp Jellyfish_game_UPDATE-02)
  + Load nhân vật và hiệu ứng animation (Jellyfish_game_UPDATE-03)
  + Chỉnh tốc độ và chạy màn hình (Jellyfish_game_UPDATE-04)
  + Nạp và điều chỉnh hướng đạn cho nhân vật (Jellyfish_game_UPDATE-05)
  + Thêm kẻ địch (Jellyfish_game_UPDATE-06)
  + Xử lý va chạm (Jellyfish_game_UPDATE-07)
  + Thêm text (Jellyfish_game_UPDATE-08)
  + Load BOSS (Jellyfish_game_UPDATE-09)
    
    - HỌC TỪ LAZY FOO : SDL Tutorial:
  + Thêm sound nền, cho đạn và update đạn của boss (Jellyfish_game_UPDATE-11)
  + Cập nhật chiến thắng cho Game (Jellyfish_game_UPDATE-12)

    - Tự code:
      + Tăng tốc độ game khi đủ điểm (Jellyfish_game_UPDATE-13)
      + Thêm mạng khi ăn đủ bánh (Jellyfish_game_UPDATE-14)
____________________
**3. Cách chơi:**
  - Vượt chướng ngại vật
  - Di chyển bằng dấu mũi tên trái phải, nhảy lên nhấn chuột phải, bắn đạn nhấn chuột trái
  - Có 3 mạng, chạm vào quái hoặc đạn của quái thì mất 1 mạng
  - Bắn đạn vào 1 quái thì +1 mark, ăn 1 bánh donut +1 donut
  - Mỗi khi được thêm 20 điểm thì game sẽ nhanh hơn x2, x3.
  - Mỗi khi được thêm 15 bánh donut thì sẽ thêm 1 mạng
  - Diệt boss phải bắn liên hòan vào boss thì mới được
  - Đạn của boss 3s được bắn 1 lần, nhưng là diện rộng sát thương là 4 ô
  - Có 1 số cơ chế riêng của game phải tự tìm hiểu
  - Thời gian giới hạn trong 400s chơi để về đích
  - Kết thúc trò chơi là về được nhà.

    _______________
**4. Hướng dẫn chơi chi tiết**
- Mở đầu:
  ![startgame](https://github.com/user-attachments/assets/321ce82e-be25-427f-b968-e2a4becab4d6)

  NHÁY CHUỘT ĐỂ BẮT ĐẦU
  
- Nhân vật chính :
  
 ![jellyfish](https://github.com/user-attachments/assets/259831a2-e00e-478c-a0f3-1a6cc0ddf2e3) 

  DI CHUYỂN SANG TRÁI PHẢI NHỜ NÚT MŨI TÊN TRÁI PHẢI TRÊN BÀN PHÌM
  NHẢY LÊN NHÁY CHUỘT PHẢI
  BẮN ĐẠN NHÁY CHUỘT TRÁI

- Threat:
  
  **Boos**
  ![1](https://github.com/user-attachments/assets/c6c20962-ca75-4b89-97f6-bdf1dfe121d4)

  BẮN RA LÓC XOÁY MỖI 3S, SẮT THƯƠNG RỘNG 4 Ô

  **Quái thường**
  ![threat_level](https://github.com/user-attachments/assets/85c5cde5-677b-480c-bb43-91ad9674998f)
  
  ![threat_left](https://github.com/user-attachments/assets/a51da0c1-a539-424d-9980-076008b9e0f0)

  Nếu main chạm phải địch thì trừ 1 mạng
  
- Đạn:

  ![sphere](https://github.com/user-attachments/assets/bf9f93a3-be0f-411a-ab08-6db5ed193d93)
  
	ĐẠN CỦA MAIN
  Có thể bắn xuyên tường
  
  ![storm](https://github.com/user-attachments/assets/d9807c93-ea2d-4b27-8ead-62efd060f6c5)
  
  ![laser](https://github.com/user-attachments/assets/201f9f84-7c56-4126-ab5e-1083c3100b5c)

  	ĐẠN CỦA ĐỊCH
  Nếu main chạm đạn địch là sẽ bị trừ 1 mạng
  Chạm vào đạn của threat con thì đạn của nó sẽ hết trong lượt chơi lại sau
  Chạm vào của boss thì boss vẫn tiếp tục nhả đạn mà khồn mất đi

- Giao diện chơi:

 ![Screenshot (34)](https://github.com/user-attachments/assets/370f0dfa-984f-4d86-a2ed-7f43a8612a2d)

- Bảng đếm mạng, bánh donut, điểm, thời gian:

![z6542445577260_ed47b041bb11b0d0b51113c103c29f38](https://github.com/user-attachments/assets/2af5017b-08ee-4762-8862-a54364ae10c7)

- Muốn bắn chết boss thì phải bắn nhiều và random sẽ tiêu diệt được boss

- Cuối cùng về lâu đài:

  ![castle](https://github.com/user-attachments/assets/5f07b391-2c71-4ea2-8582-13083e0372d6)

- Về đến lâu đài là trò chơi kết thức, chiến thắng:

  ![win](https://github.com/user-attachments/assets/08ce3de1-958d-48cc-8db8-d095c9fd4014)

- Trong trường hợp hết thời gian, hoặc hết 3 mạng thì game sẽ thua:

  ![image](https://github.com/user-attachments/assets/91135557-afec-451c-b27a-95127e98f81e)


________________
**5. Về các nguồn làm game**

**Về source code game:**

1.	 Main.cpp – Hàm chính của game
✅ Chức năng chính:
•	Khởi tạo SDL, TTF, IMG, âm thanh
•	Hiển thị màn hình bắt đầu (IMG/startgame.png)
•	Tạo các đối tượng: map, player, threats (quái), boss, castle, power, donut, explosion
•	Vòng lặp game chính: xử lý input, update, render, xử lý va chạm
•	Kiểm tra chiến thắng (khi chạm lâu đài), thua (hết máu, hết thời gian)
➡️ Các phần quan trọng:
•	InitData() → khởi tạo SDL
•	startScreen.Render() → hiện màn hình chờ nhấn chuột
•	MakeThreadList() → khởi tạo list quái
•	while (!is_quit) → vòng lặp game chính
o	Input: SDL_PollEvent, p_player.HandelInputAction()
o	Player: DoPlayer(), Show(), HandleBullet()
o	Threats: DoPlayer(), Show(), MakeBullet()
o	Boss: DoPlayer(), MakeBullet(), Show()
o	Map: DrawMap()
o	Va chạm: SDLCommon::CheckCollision
o	HUD: time_game.RenderText(), mark_game.RenderText(), donut_game.RenderText()
•	Hiệu ứng nổ: exp_main.Show(), exp_threat.Show()
•	Thoát game: close(), SDL_Quit()
_______________________________________________
2.	 MainObject.cpp / MainObject.h – Đối tượng người chơi (player)
✅ Chức năng chính:
•	Quản lý vị trí, di chuyển, nhảy, rơi, bắn, trạng thái
•	Xử lý input: trái/phải/nhảy/bắn
•	Kiểm tra va chạm với map: ăn donut, va chạm tile
•	Trung tâm hoá camera theo player
•	Quản lý danh sách đạn
➡️ Hàm quan trọng:
•	LoadImg() → load ảnh nhân vật
•	HandelInputAction() → xử lý input bàn phím, chuột
•	DoPlayer() → xử lý di chuyển & update trạng thái
•	CheckToMap() → va chạm map, update vị trí
•	CenterEntityOnMap() → giữ player giữa màn hình
•	HandleBullet(), RemoveBullet() → quản lý đạn
•	IncreaseDonut() → tăng đếm donut
•	UpdateImagePlayer() → đổi ảnh (nhảy/đi bộ)
____________________________________
3.	 ThreatsObject.cpp / ThreatsObject.h – Đối tượng kẻ địch (threat)
✅ Chức năng chính:
•	Quản lý vị trí, di chuyển (tĩnh/di chuyển qua lại)
•	Bắn đạn
•	Kiểm tra va chạm map
•	Render animation
•	Quản lý danh sách đạn
➡️ Hàm quan trọng:
•	LoadImg() → load ảnh kẻ địch
•	set_clips() → chia frame animation
•	DoPlayer() → di chuyển + gravity
•	CheckToMap() → kiểm tra va chạm map
•	ImpMoveType() → AI di chuyển qua lại
•	MakeBullet() → bắn đạn
•	InitBullet() → khởi tạo viên đạn
__________________________________________
4.	 BossObject.cpp / BossObject.h – Đối tượng boss
✅ Chức năng chính:
•	Boss di chuyển, bắn đạn, AI, va chạm map
•	Độc lập với threats bình thường
•	Quản lý danh sách đạn boss
➡️ Hàm quan trọng:
•	LoadImgFrames() → load 4 frame ảnh boss
•	DoPlayer() → xử lý AI
•	CheckToMap() → kiểm tra va chạm map
•	MakeBullet(), InitBullet() → quản lý đạn
•	Show() → vẽ boss lên màn hình
___________________________________________________-
5.	 BulletObject.cpp / BulletObject.h – Đối tượng đạn
✅ Chức năng chính:
•	Di chuyển đạn, vẽ đạn
•	Quản lý kiểu đạn (SPHERE, LASER, STORM)
•	Quản lý animation đạn storm
➡️ Hàm quan trọng:
•	LoadImgBullet() → load ảnh đạn theo loại
•	HandleMove() → xử lý di chuyển trái/phải
•	Render() → vẽ đạn (có/không animation)
•	set_clips() → animation clip
________________________________
6.	 ExplosionObject.cpp / ExplosionObject.h – Hiệu ứng nổ
✅ Chức năng chính:
•	Quản lý animation nổ
•	Dùng khi player, threat, boss nổ tung
➡️ Hàm quan trọng:
•	LoadImg() → load ảnh nổ
•	set_clip() → chia clip animation
•	Show() → hiển thị frame nổ
_______________________________________________________
7.	 game_map.cpp / game_map.h – Bản đồ tile
✅ Chức năng chính:
•	Load map từ file (.dat)
•	Load tile image (map/0.png → map/19.png)
•	Render map theo camera
➡️ Hàm quan trọng:
•	LoadMap() → đọc file map
•	LoadTiles() → load ảnh tile
•	DrawMap() → vẽ tile hiển thị trên screen
___________________________________________________
8.	 PlayerPower.cpp / PlayerPower.h – Hiển thị máu & donut
✅ Chức năng chính:
•	Hiển thị số mạng còn
•	Hiển thị donut HUD
•	Tăng/giảm mạng
➡️ Hàm quan trọng:
•	Init() → load ảnh power (máu)
•	Show() → hiển thị lên screen
•	Decrease(), InitCrease() → giảm/tăng mạng
•	PlayerDonut::Init(), Show() → hiển thị donut HUD
_________________________________________________
9.	SoundManager.cpp / SoundManager.h – Quản lý âm thanh
✅ Chức năng chính:
•	Quản lý nhạc nền + hiệu ứng bắn
•	Singleton pattern
➡️ Hàm quan trọng:
•	init() → khởi tạo SDL_mixer + load nhạc/âm
•	playMusic() → phát nhạc nền
•	playShot() → phát âm thanh bắn
•	clean() → free âm thanh
________________________________________
10.	 TextObject.cpp / TextObject.h – Hiển thị chữ
✅ Chức năng chính:
•	Render text lên màn hình
•	Đổi màu text (red, white, blank)
➡️ Hàm quan trọng:
•	LoadFromRenderText() → tạo texture từ string
•	RenderText() → vẽ text
•	SetColor() → đặt màu chữ
•	SetText() → đặt nội dung text
_______________________________________________________
11.	 Geometric.cpp / Geometric.h – Vẽ hình cơ bản
✅ Chức năng chính:
•	Vẽ hình chữ nhật tô màu
•	Vẽ viền chữ nhật
➡️ Hàm quan trọng:
•	RenderRectangle() → fill hình
•	RenderOutline() → vẽ viền
_____________________________________________________
12.	 BaseObjects.cpp / BaseObjects.h – Đối tượng cơ sở
✅ Chức năng chính:
•	Quản lý SDL_Texture, rect, load/render ảnh
•	Class cha cho player, threats, boss, tile, explosion
➡️ Hàm quan trọng:
•	LoadImg() → load ảnh
•	Render() → vẽ
•	Free() → giải phóng texture
_____________________________________________________
13.	ImpTimer (ImpTime.h / ImpTime.cpp)
✅ Chức năng chính:
•	Cung cấp bộ đếm thời gian (timer) cho game, đo thời gian trôi qua, hỗ trợ tạm dừng và tiếp tục.
•	Thường dùng để tính delta-time, điều khiển tốc độ spawn, đếm ngược, v.v.
➡️ Hàm quan trọng: 
•	void start()  Đánh dấu timer đã bắt đầu 
•	void stop() Đặt lại trạng thái chưa khởi động 
•	void paused()Nếu timer đang chạy và chưa paused,
•	void unpaused()
•	int get_ticks() Trả về số ms đã trôi qua kể từ start() (hoặc kể từ lúc unpaused sau cùng).
•	bool is_started() / bool is_paused()  Trả trạng thái hiện tại của timer (true/false).
____________________________________________________________
14.	Common (Common.h/Common.cpp)
✅ Chức năng chính:
•	Khởi tạo & đóng SDL: thiết lập SDL_Window, SDL_Renderer, khởi PNG, Mixer, TTF…
•	Load dữ liệu chung: background, tile map, cấu hình màn hình…
•	Quản lý cấu trúc Map: lưu lưới ô vuông, kích thước, vị trí bắt đầu.
•	Kiểm tra va chạm: hàm chung CheckCollision dùng cho mọi object.
➡️ Hàm quan trọng: 
•	bool InitData()  khởi tạo SDL
•	bool LoadBackground()  load ảnh nền
•	void close()  giải phóng
•	CheckCollision  check va chạm, trồng chéo tile vuông.

___________________________________

Main.cpp
 ├── PlayerPower (HUD)
 ├── MainObject (player)
 ├── ThreatsObject (kẻ địch)
 ├── BossObject (boss)
 ├── BulletObject (đạn)
 ├── ExplosionObject (nổ)
 ├── GameMap (map tile)
 ├── SoundManager (nhạc)
 ├── TextObject (chữ)
 └── Geometric (vẽ HUD)
 ├── ImpTimer (Thời gian)


**Về đồ họa:**
  
  - Ảnh nền do chatgpt cung cấp
  - Đồ họa khác lấy ở OpenGameArt.org, vi.pngtree.com

**ÂM THANH**

- OpenGameArt.org
- Youtube
