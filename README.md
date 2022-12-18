# Bài tập lớn môn Đồ Họa Máy Tính: Mô phỏng Hệ Mặt Trời

![solar-system](/assets/solar_system.png)

## Mục lục

- [Đề tài](#đề-tài)

- [Sinh viên thực hiện](#sinh-viên-thực-hiện)

- [Cài đặt và sử dụng](#cài-đặt-và-sử-dụng)

## Đề tài

- Mô phỏng hệ mặt trời
- Ngôn ngữ: C++
- Thư viện: OpenGl/Freeglut

## Sinh viên thực hiện

`Nguyễn Văn Khánh Duy - 2051067158`
>[![Facebook](https://img.shields.io/badge/Facebook-1877F2?style=for-the-badge&logo=facebook&logoColor=white)](https://www.facebook.com/khanhduy.tls.4/)

`Nguyễn Hoài Nguyệt An - 2051067525`
>[![Facebook](https://img.shields.io/badge/Facebook-1877F2?style=for-the-badge&logo=facebook&logoColor=white)](https://www.facebook.com/profile.php?id=100012224136535)

`Nguyễn Phạm Xuân Hiền - 2051067165`
>[![Facebook](https://img.shields.io/badge/Facebook-1877F2?style=for-the-badge&logo=facebook&logoColor=white)](https://www.facebook.com/profile.php?id=100013313088490)

`Nguyễn Phùng Hưng - 2051067550`
>[![Facebook](https://img.shields.io/badge/Facebook-1877F2?style=for-the-badge&logo=facebook&logoColor=white)](https://www.facebook.com/profile.php?id=100013314739498)

## Cài đặt và sử dụng

### Hệ điều hành Windows

- `Trình biên dịch MinGW`

    [Tải trình biên dịch tại đây](https://sourceforge.net/projects/mingw/)

    [Chi tiết cài đặt trình biên dịch và thiết lập biến môi trường tại đây](https://exploreshaifali.github.io/2014/07/18/Using-GCC-Compiler-on-Windows/)
- `Thư viện Freeglut`

    [Tải thư viện tại đây](https://www.transmissionzero.co.uk/files/software/development/GLUT/freeglut-MinGW.zip)

- `Hướng dẫn cài đặt`

    [Phần 1: Cài đặt các công cụ cần thiết](https://drive.google.com/file/d/10NO6MU0-Wnt8Rl3QeyH46JKeZIPqzsC2/view?usp=share_link)

    [Phần 2: Thiết lập biến mối trường và cài đặt thư viện Freeglut](https://drive.google.com/file/d/1TmaEnSeaLxLrGOr5vSwb1zg2pVkO-ckG/view?usp=share_link)

    [Phần 3: Cấu hình VScode cho OpenGL/Freeglut (Tùy chọn)](https://drive.google.com/file/d/1_5oRkv2Ts5rZBe3-5oghV7E27Ve2oPis/view?usp=share_link)

- `Script cấu hình VScode cho OpenGL/Freeglut (Tùy chọn)`

```bash
"cd $dir && g++ -g -Wall $fileName -lopengl32 -lglu32 -lfreeglut -o $fileNameWithoutExt && start cmd /k \"$dir$fileNameWithoutExt && pause && del /f $dir$fileNameWithoutExt.exe && exit\""
```

- `Thực hiện chạy phần mềm mô phỏng`

    [Tải mã nguồn tại đây](https://github.com/duynguyen02/solar-system/archive/refs/heads/main.zip)

Sau khi tải và giải nén mã nguồn, nhấn đúp vào file `run.bat` để thực hiện biên dịch và thực thi mã nguồn. Nếu xảy ra lỗi, vui lòng kiểm tra lại mục cài đặt trình biên dịch và thư viện [phía trên](#cài-đặt-và-sử-dụng)

### Hệ điều hành Linux

- `Yêu cầu hệ điều hành`

Ubuntu và các distro tương tự (Debian, Lubuntu, Bodhi,... ). Nếu sử dụng các distro khác vui lòng tải các package tương tự được nêu ra phía dưới.

- `Cài đặt công cụ và thư viên`

- git
- build-essential
- freeglut3
- freeglut3-dev
- mesa-utils

```bash
sudo apt-get update
sudo apt-get install git
sudo apt-get install build-essential
sudo apt-get install freeglut3
sudo apt-get install freeglut3-dev
sudo apt-get install mesa-utils
```

- `Thực hiện chạy phần mềm mô phỏng`

```bash
git clone https://github.com/duynguyen02/solar-system
cd solar-system
chmod +x run.sh
./run.sh
```
