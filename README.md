# Magic Cat Escape Game
Game Demo: [Drive](https://drive.google.com/drive/folders/1y145l8k_fbSVxe4xHGGMzr8AVTDx0-fG?usp=drive_link)

## Giới thiệu Game
Magic Cat là game được làm lại dựa trên game gốc Magic Cat Academy của Google. Người chơi vào vai một chú mèo ma thuật có khả năng tạo ra các phép thuật giúp tiêu diệt quái vật bằng việc vẽ các nét vẽ lên màn hình. Nhiệm vụ của bạn là tiêu diệt thật nhiều quái vật để đạt điểm số cao nhất có thể.

## Cách tải Game
1. Vào trang GitHub của dự án.
2. Bấm nút "Code" (màu xanh lá, nằm gần đầu trang).
3. Chọn "Download ZIP".
4. Giải nén file ZIP.
5. Chạy file "main.exe" để chơi Game
## Bắt đầu Game
Người chơi cần ấn phím "Enter" để có thể bắt đầu Game

<img width="1440" src="https://github.com/vuhailc06/Magic-Cat-Escape-Game/blob/master/res/images/open2.png">

## Chơi Game
- Khi trò chơi bắt đầu, quái vật sẽ liên tục di chuyển đến vị trí Magic Cat, và tấn công khi chạm vào người Magic Cat. Người chơi cần vẽ các nét vẽ bằng chuột để tiêu diệt nhiều quái vật nhất có thể để đạt số điểm cao nhất.
  
<img width ="1440" src="https://github.com/vuhailc06/Magic-Cat-Escape-Game/blob/master/res/preview/gameplay.png">

- Mỗi quái vật sẽ chứa các kí hiệu ở trên đầu, và người chơi cần vẽ đúng các nét theo thứ tự từ trái sang phải.

<img width ="500" src="https://github.com/vuhailc06/Magic-Cat-Escape-Game/blob/master/res/preview/ghost.png">

- Các kí hiệu có thể xuất hiện trên đầu quái vật

<img width ="500" src="https://github.com/vuhailc06/Magic-Cat-Escape-Game/blob/master/res/images/attackPack.png"> <img width ="300" src="https://github.com/vuhailc06/Magic-Cat-Escape-Game/blob/master/res/images/bonusHeart.png">  

- Đó cũng là các loại phép thuật mà chú mèo có thể thực hiện được, nếu người chơi vẽ đúng loại thì nét vẽ sẽ đổi màu theo, nét vẽ mặc định có màu trắng

<img width ="500" src="https://github.com/vuhailc06/Magic-Cat-Escape-Game/blob/master/res/preview/draw0.png">  
<img width ="500" src="https://github.com/vuhailc06/Magic-Cat-Escape-Game/blob/master/res/preview/draw1.png">
<img width ="500" src="https://github.com/vuhailc06/Magic-Cat-Escape-Game/blob/master/res/preview/draw2.png">  
<img width ="500" src="https://github.com/vuhailc06/Magic-Cat-Escape-Game/blob/master/res/preview/draw3.png">
<img width ="500" src="https://github.com/vuhailc06/Magic-Cat-Escape-Game/blob/master/res/preview/draw4.png">
<img width ="500" src="https://github.com/vuhailc06/Magic-Cat-Escape-Game/blob/master/res/preview/draw5.png">

- Chú mèo có tối đa 5 mạng, và sẽ mất mạng khi bị quái vật tấn công
  
<img width ="500" src="https://github.com/vuhailc06/Magic-Cat-Escape-Game/blob/master/res/preview/health.png">

- Cách thức tính điểm:
  + Vẽ trúng kí hiệu trên đầu quái vật: 5 điểm
  + Vẽ trúng hình trái tim: 10 điểm
  + Tiêu diệt quái vật: 20 điểm


## Kết thúc Game
Khi Magic Cat hết mạng, trò chơi sẽ kết thúc hiển thị số điểm của người chơi. Người chơi có thể ấn phím "R" để chơi lại.

<img width="1440" src="https://github.com/vuhailc06/Magic-Cat-Escape-Game/blob/master/res/preview/ending.png">

## Các kỹ thuật cơ bản:
- Xử lý tương tác bằng bàn phím và chuột của người chơi.
- Sử dụng đồ họa, âm thanh, text.
- Xử lý nét vẽ, nhận diện các nét vẽ cơ bản của người chơi.
- Sử dụng kiến thức toán học cơ bản để hiển thị nét vẽ, di chuyển quái vật, xử lý va chạm.

## Nguồn tài liệu nghiên cứu và tham khảo
### SDL2 và cấu trúc Game:
- [LazyFoo](https://lazyfoo.net/tutorials/SDL/)
- [codergopher](https://www.youtube.com/playlist?list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS)
- [Let's make games](https://www.youtube.com/playlist?list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx)
### Sounds and images:
- [kimduuukbae](https://github.com/kimduuukbae/Magic-Cat-Academy/tree/master/source/Resources)


