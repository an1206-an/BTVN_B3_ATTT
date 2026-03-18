#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>

using namespace std;

int bit_length(int x) {
    int length = 0;
    while (x > 0) {
        length++;
        x >>= 1;
    }
    return length;
}

// Hàm nhân (GF2)
int gf2_mul(int a, int b) {
    int res = 0;
    while (b > 0) {
        if (b & 1) res ^= a; 
        a <<= 1;            
        b >>= 1;             
    }
    return res;
}

// Hàm chia GF(2) Thương (q), Dư (r)
void gf2_div(int a, int b, int &q, int &r) {
    if (b == 0) {
        throw invalid_argument("Loi: Chia cho 0");
    }
    q = 0;
    int len_a = bit_length(a);
    int len_b = bit_length(b);
    // Thuật toán chia đa thức nhị phân trượt
    while (len_a >= len_b) {
        int shift = len_a - len_b;
        q ^= (1 << shift);     // Ghi nhận bậc của thương số
        a ^= (b << shift);     // Triệt tiêu bậc cao nhất bằng phép XOR
        len_a = bit_length(a); // Cập nhật lại bậc của số bị chia mới
    }
    r = a; // Phần còn lại không chia được nữa chính là số dư
}

// Euclidean mở rộng 
void extended_euclidean_gf2(int m, int a) {
    int r_prev = m, r_curr = a;
    int v_prev = 1, v_curr = 0;
    int w_prev = 0, w_curr = 1;
    // In bảng
    cout << left << setw(4) << "i" << " | " 
         << setw(5) << "r_i" << " | " 
         << setw(5) << "q_i" << " | " 
         << setw(5) << "v_i" << " | " 
         << setw(6) << "w_i" << endl;
    cout << string(36, '-') << endl;
    cout << left << setw(4) << "-1" << " | " 
         << setw(5) << r_prev << " | " 
         << setw(5) << "-" << " | " 
         << setw(5) << v_prev << " | " 
         << setw(6) << w_prev << endl;
    cout << left << setw(4) << "0" << " | " 
         << setw(5) << r_curr << " | " 
         << setw(5) << "-" << " | " 
         << setw(5) << v_curr << " | " 
         << setw(6) << w_curr << endl;
    int i = 1;


    while (r_curr != 0) {
        int q, r_next;
        gf2_div(r_prev, r_curr, q, r_next);
        
        // Tính v_i và w_i
        int v_next = v_prev ^ gf2_mul(q, v_curr);
        int w_next = w_prev ^ gf2_mul(q, w_curr);
        
        // In 
        cout << left << setw(4) << i << " | " 
             << setw(5) << r_next << " | " 
             << setw(5) << q << " | " 
             << setw(5) << v_next << " | " 
             << setw(6) << w_next << endl;
             
        // Cập nhật
        r_prev = r_curr;
        r_curr = r_next;
        v_prev = v_curr;
        v_curr = v_next;
        w_prev = w_curr;
        w_curr = w_next;
        i++;
    }
    
    cout << string(36, '-') << endl;
    if (r_prev == 1) {
        cout << "=> Nghich dao nhan la: " << w_prev << endl;
    } else {
        cout << "=> Khong ton tai nghich dao" << endl;
    }
    cout << endl;
}
int main() {
    int m_poly = 1033; // m(x) = x^10 + x^3 + 1
    int a_val = 523;   
    int b_val = 1015;  
    cout << "Tim nghich dao cua a = " << a_val << endl;
    extended_euclidean_gf2(m_poly, a_val);
    cout << "Tim nghich dao cua b = " << b_val << endl;
    extended_euclidean_gf2(m_poly, b_val);
    return 0;
}