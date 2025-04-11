# Coding Convention: 

- **Dấu ngoặc nhọn(Braces): Luôn sử dung dấu ngoặc nhọn {} cho các khối lệnh, ngay cả khi chỉ có một câu lệnh**
    - **Ví dụ:**
        if (condition) {
        doSomething();
        }   
- **Đặt tên:** Có ý nghĩa với biến, hàm, class. Với hàm sử dụng camelCase, biến sử dụng snake_case, và Class sử dụng PascalCase. Với hàng số sử dụng SCREAMING_SNAKE_CASE
- **Khi xây dựng Class cần tối ưu hóa phạm vi:** Chỉ để lộ những gì cần thiết trong public, Sử dụng private và protected cho dữ liệu và hàm nội bộ.
- **Sắp xếp include:** Ưu tiên thứ tự là hệ thống, bên thứ ba, nội bộ dự án
    - **Ví dụ:**
    #include <iostream>
    #include <vector>
    #include "third_party/lib.h"
    #include "my_project/utils.h"
- **Viết comment rõ ràng:** Có nghĩa là giải thích tại sao cho code của của mình. Nếu có thể hãy sử dụng comment kiểu Doxygen cho các hàm quan trọng
    - **Ví dụ:**
    /*
    * Calculates the area of a rectangle.
    * @param width The width of the rectangle.
    * @param height The height of the rectangle.
    * @return The area of the rectangle.
    */
    int calculateArea(int width, int height);
- **Không cầm thêm so sánh dư thừa bằng con trỏ**
    - **Ví dụ:**
    if(p) thay vì if(p == nullptr)
- **Ưu tiên pre increment(++i) hơn là post increment(i++)**
- **Không sử dụng namespace std trong header file hoặc file toàn cục  để tránh xung đột**
- **Không sử dụng endl**
- **Không khai báo biến trên cùng một dòng**
- **Ví dụ:** int *p, *q, *r, *s
- **Sử dụng nullptr thay cho NULL**
- **Ưu tiên hàm pure. Có nghĩa là không thay đổi biến bên ngoài. Chỉ nhận vào giá trị và trả về giá trị cần thiết**
- **Khi viết hàm ưu tiên return nhanh nhất, không dồn về cuối mới return.**
- **Ưu tiên xử lí exception thay vì né tránh**
- **Quản lí bộ nhớ:** Ưu tiên Smart Pointers sử dụng std::unique_ptr hoặc std::shared_ptr thay vì con trỏ thô (raw_pointers). Ngoài ra luôn kiểm tra việc giải phóng tài nguyên trong destructor. Không sử dụng new/delete trực tiếp trừ khi cần thiết.
- **Sử dụng git commit message rõ ràng**
    - **Ví dụ:** add user authentication module:
    - Implement login functionality
    - Check OTP
- **Khi viết hàm nên tối ưu hóa không quá dài. Để dễ bảo trì. Ưu tiên các hàm có thể tái sử dụng**
- **Ưu tiên truyền tham chiếu vào để tránh copy**
    -**Ví dụ:**
    extractName(const string& s) thay vì extractName(string s)
- **dùng Yoda condition**
    -**Ví dụ:**
    if (404 == statusCode) thay vì if (statusCode == 404)





