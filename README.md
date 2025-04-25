![image](https://github.com/user-attachments/assets/71b126ba-b3f5-4f6a-ba99-49af12ac5af5)
# Jellyfish_game

**Hành trình về nhà của sứa con**

**Vid Demo**
-	https://www.youtube.com/watch?v=v7mQaT61soo

**1. Giới thiệu:**

   Jellyfish Game là thử thách tìm đường của 1 chú Sứa con bị lạc giữa vùng biển xa xôi. Sứa phải vượt qua các trở ngại trên đường và tiêu diệt chúng, ăn bánh trên đường để lớn hơn, diện mạo đẹp hơn. Cuối cùng, Sứa phải gặp Boss cuối trước cửa về nhà, chỉ cần tiêu diệt đươc con Boss này, chú Sứa sẽ hoàn thành nhiệm vụ và về nhà thành công.
   _________________
**2. Tiến trình:**

    - THAM KHẢO TỪ YOUTOBE : Học Lập Trình Game C++ SDL Giới Thiệu Phần 2:
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
____________________
**3. Cách chơi:**
  - Vượt chướng ngại vật
  - Di chyển bằng dấu mũi tên trái phải, nhảy lên nhấn chuột phải, bắn đạn nhấn chuột trái
  - Có 3 mạng, chạm vào quái hoặc đạn của quái thì mất 1 mạng
  - Bắn đạn vào 1 quái thì +1 mark, ăn 1 bánh donut +1 donut
  - Diệt boss phải bắn liên hoan vào boss thì mới được
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

🟦 Main.cpp

	- Hàm main()
 
	- Vòng lặp chính của game
 
	- Xử lý:
		+ Hiển thị màn hình
  
	   	+ Giao tiếp giữa các object
     
   		+ Xử lý va chạm, mạng, điểm số, thời gian, game over
     

⸻

🔸 Common.h + Common.cpp

	•  Biến toàn cục, định nghĩa SDL_Renderer, màu vẽ, cấu hình
 
	•  Hàm CheckCollision(): check va chạm giữa hai hình chữ nhật
 
   	•  Các macro quan trọng
    
⸻

🟧 BaseObjects.h + BaseObjects.cpp

	•	Lớp cơ sở cho mọi object có hình ảnh (LoadImg, Render, GetRect)
 
	•	Được kế thừa bởi Player, Threat, Boss, Bullet

⸻

🟩 MainObject.h + MainObject.cpp

   •	Di chuyển, nhảy, bắn đạn, va chạm, thu thập donut
   
   •    Nhân vật chính: jellyfish 
   
   •  	LoadImg: load ảnh của main
   
   •  	GetRectFrame: lập tạo độ
   
   •  	set_clips() → quản lý animation của player
   
   •  	Show: di chuyển của main, chuyển qua từng frame -> animation
   
   • 	HandelInputAction: hàm nhập để điều khiển main
   
   •` 	HandleBullet: xử lý đạn bắn
   
   • 	RemoveBullet: đạn mất khi đâm vào threat hoặc rời khỏi tầm nhìn của main
   
   •  	DoPlayer: xử lý tạo độ di chuyển, nếu mà bị die hoặc rớt vực lùi lại 4 ô(so với tile map)
   
   •  	CenterEntityOnMap: cho bản ddoof di chuyển theo main ở chính giữa
   
   •  	CheckToMap: check di chuyển ăn donut
   
   •  	IncreaseDonut: tăng donut_count
   
   •  	UpdateImagePlayer: load ảnh chạy hoặc nhảy

⸻

🟥 ThreatsObject.h + ThreatsObject.cpp

	•	Kẻ địch (threats): di chuyển hoặc đứng yên bắn
 
	•	Gồm AI đơn giản (di chuyển trái/phải)
 
	•	Bắn đạn, xử lý va chạm với player
 
   •  	LoadImg, GetRectFrame, set_clips, Show, DoPlayer, RemoveBullet, CheckToMap tương tự trong MainObject
   
   •  	InitThreats: di chuyển qua lại từ tọa độ Ox từ a đến b
   
   •  	ImpMoveType: load ảnh trái phải của threat
   
   •  	InitBullet: nạp đạn và khoảng cách đạn đi cho threat
   
   • 	MakeBullet: cập nhật và lặp lại đạn bắn

 **TỪ ĐÂY CÁC HÀM NÀO GIỐNG TRÊN SẼ KHÔNG GỌI LẠI NỮA VÌ CHÚNG CÓ CHỨC NĂNG TƯƠNG TỰ **
⸻

🟨 BossObject.h + BossObject.cpp

	•	Boss cuối map (Giant)
 
	•	Có hoạt ảnh riêng
 
	•	Bắn đạn (storm)
 
	•	Xuất hiện khi player đi đủ xa
 
	•	Có MakeBullet(), Show(), InitBullet()
 
   •	LoadImgFrames: load animation cho Boss != set_clips
 
⸻

🟦 BulletObject.h + BulletObject.cpp

	•	Đại diện cho đạn:
 
	•	LASER_BULLET
 
	•	SPHERE_BULLET
 
	•	STORM_BULLET (4 frame animation)
 
	•	Có animation, hướng bay, tốc độ, va chạm

⸻

🟫 ExplosionObject.h + ExplosionObject.cpp

	•	Hiệu ứng nổ 💥
 
	•	Có frame animation
 
	•	Dùng khi va chạm → tạo hiệu ứng sống động

⸻

⚫ TextObject.h + TextObject.cpp

	•	Hiển thị chữ (Text): thời gian, điểm, mạng
 
	•	Sử dụng TTF_Font và SDL_ttf
 
	•	SetText(), RenderText()

⸻

⚪ PlayerPower.h + PlayerPower.cpp

	•	Hiển thị mạng sống (💛 trái tim)
 
	•	Hiển thị số donut thu thập được
 
	•	Init(), Render(), Decrease()

⸻

🟪 SoundManager.h + SoundManager.cpp

	•	Phát nhạc nền & hiệu ứng
 
	•	Quản lý âm thanh toàn cục (singleton)

⸻

🔷 game_map.h + game_map.cpp

	•	Quản lý bản đồ (tile map)
 
	•	LoadMap(), DrawMap(), GetMap()
 
	•	Quét và hiển thị tile theo camera

⸻

🟩 Geometric.h + Geometric.cpp

	•	Vẽ hình chữ nhật UI (thanh thời gian, khung điểm,…)
 
	•	RenderRectangle(), RenderOutline()

⸻

🕐 ImpTime.h + ImpTime.cpp

	•	Đồng hồ thời gian game
 
	•	start(), get_ticks(), pause()
______

**Về đồ họa:**
  
  - Ảnh nền do chatgpt cung cấp
  - Đồ họa khác lấy ở OpenGameArt.org
