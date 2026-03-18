#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// Hàm chuẩn bị chuỗi
void chuanbichuoi(string &s) {
    string res = "";
    for (char c : s) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I';
            res += c;
        }
    }
    s = res;
}

// Hàm tạo ma trận 5x5 từ khóa
void taoMatran(string key, char matrix[5][5]) {
    bool used[26] = {false};
    used['J' - 'A'] = true; // Mặc định J được coi như I
    
    string combinedKey = "";
    // Thêm các chữ cái của từ khóa vào trước
    for (char c : key) {
        if (!used[c - 'A']) {
            combinedKey += c;
            used[c - 'A'] = true;
        }
    }
    // Thêm các chữ cái còn lại trong bảng chữ cái
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            combinedKey += c;
        }
    }
    
    // Đổ vào ma trận 5x5
    int idx = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = combinedKey[idx++];
        }
    }
}

// Hàm chuẩn bị bản rõ (thêm X vào giữa 2 ký tự giống nhau và X vào cuối nếu lẻ)
string formatPlaintext(string p) {
    string res = "";
    for (size_t i = 0; i < p.length(); i++) {
        res += p[i];
        // Nếu 2 ký tự liên tiếp giống nhau, chèn thêm 'X'
        if (i + 1 < p.length() && p[i] == p[i+1]) {
            res += 'X';
        }
    }
    // Nếu tổng chiều dài lẻ, thêm 'X' vào cuối
    if (res.length() % 2 != 0) res += 'X';
    return res;
}

// Hàm tìm tọa độ (hàng, cột) của một ký tự trong ma trận
void findPosition(char matrix[5][5], char c, int &row, int &col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                row = i; col = j; return;
            }
        }
    }
}

// Hàm thực hiện mã hóa
string playFair(string pt, char matrix[5][5]) {
    string ct = "";
    for (size_t i = 0; i < pt.length(); i += 2) {
        int r1, c1, r2, c2;
        findPosition(matrix, pt[i], r1, c1);
        findPosition(matrix, pt[i+1], r2, c2);
        
        if (r1 == r2) {
            // Quy tắc 1: Cùng hàng -> Dịch phải 1 ô
            ct += matrix[r1][(c1 + 1) % 5];
            ct += matrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            // Quy tắc 2: Cùng cột -> Dịch xuống 1 ô
            ct += matrix[(r1 + 1) % 5][c1];
            ct += matrix[(r2 + 1) % 5][c2];
        } else {
            // Quy tắc 3: Khác hàng, khác cột -> Lấy góc đối diện
            ct += matrix[r1][c2];
            ct += matrix[r2][c1];
        }
        ct += " "; 
    }
    return ct;
}

int main() {
    string key = "MONARCHY";
    string plaintext = "DO YOU LIKE TO STUDY A CRYPTOGRAPHY COURSE";
    cout << "Key: " << key << endl;
    cout << "Van ban: " << plaintext << endl;
    
    // Xử lý chuỗi đầu vào
    chuanbichuoi(key);
    chuanbichuoi(plaintext);
    plaintext = formatPlaintext(plaintext);
    
    // Tạo ma trận
    char matrix[5][5];
    taoMatran(key, matrix);
    
    // Mã hóa
    string ciphertext = playFair(plaintext, matrix);
    cout << "Ban ma:\n" << ciphertext << endl;
    return 0;
}