# 📚 Quản lý Cửa Hàng Cho Thuê Truyện  
Bằng Cấu Trúc **Stack** và **Queue** (danh sách liên kết đơn)

---

## ✅ Nguyên tắc làm
- [ ] Làm từng bước theo thứ tự
- [ ] Test kỹ mỗi phần trước khi sang phần tiếp theo
- [ ] Ghi chú cá nhân khi cần (bug, ý tưởng cải tiến...)

---

## 🧱 Yêu cầu 1: Hiện thực **Stack** (danh sách liên kết đơn)

### Chức năng cơ bản
- [ ] Khai báo cấu trúc dữ liệu **Truyện** (mã, tên, tác giả, thể loại, tập số, đơn giá thuê/ngày, tình trạng)
- [ ] Cài đặt Node và Stack (Push, Pop, Top)

### Quản lý kho truyện bằng Stack
- [ ] **Thêm quyển truyện mới (Push)**  
  Mỗi quyển mới nhập được đưa lên đỉnh Stack
- [ ] **Xem truyện mới nhập gần nhất (Top)**  
  Hiển thị truyện trên đỉnh Stack
- [ ] **Xóa truyện nhập sai (Pop)**  
  Loại bỏ truyện mới nhập nhầm (Undo nhập sai)

### Quản lý lịch sử và undo
- [ ] **Stack log cho thuê**  
  Ghi nhận mỗi lần khách thuê truyện
- [ ] **Hoàn tác thao tác (Undo)**  
  Sử dụng stack thao tác để quay lại bước trước

### Hiển thị & tạm lưu
- [ ] **In truyện theo thứ tự nhập kho** (truyện mới nhập in trước)  
- [ ] **Tạm lưu truyện đang xử lý** (push vào stack tạm, pop ra khi xong)

---

## 🧱 Yêu cầu 2: Hiện thực **Queue** (danh sách liên kết đơn)

### Chức năng cơ bản
- [ ] Khai báo Queue và Node
- [ ] Cài đặt Enqueue, Dequeue, Peek

### Quản lý mượn trả bằng Queue
- [ ] **Quản lý hàng chờ mượn truyện**  
  Khi truyện đang được thuê, khách sau sẽ xếp hàng
- [ ] **Nhập kho truyện theo lô (enqueue)**  
  Truyện mới nhập đưa vào queue, FIFO
- [ ] **Xử lý truyện trả về (enqueue -> dequeue)**  
  Truyện trả xếp vào hàng chờ kiểm định, xử lý FIFO
- [ ] **Xử lý mượn truyện theo thứ tự yêu cầu**  
  Nhiều yêu cầu cùng lúc thì xử lý FIFO

### Báo cáo lịch sử
- [ ] **Lịch sử mượn-trả theo thời gian**  
  In báo cáo từ đầu đến cuối Queue

---

## 📌 Hướng dẫn thực hiện
1. Viết trước phần **cấu trúc dữ liệu (Node, Stack, Queue)**  
2. Làm lần lượt các chức năng nhỏ, tick vào checklist sau mỗi bước  
3. Test với dữ liệu mẫu (ví dụ 2–3 quyển truyện, 2 khách thuê...)  
4. Cuối cùng hoàn thiện báo cáo hoặc menu chương trình tổng hợp  

---
