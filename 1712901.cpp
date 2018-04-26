#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include <io.h>   
#include<conio.h>
struct SOTHICH
{
	wchar_t* ST[100];
	int n;
};
struct SinhVien
{
	wchar_t* MSSV;
	wchar_t* HoTen;
	wchar_t* Khoa;
	int Khoa1;
	wchar_t* NgaySinh;
	wchar_t* HinhAnh;
	wchar_t* MoTa;
	SOTHICH Sothich;

};
int Wlen(wchar_t *s)
{
	int i = 0;
	if (s == NULL) return -1;
	while (*(s + i) != L'\n'&&*(s + i) != '\0')
	{
		i++;
	}
	return i;
}
void TOKen(wchar_t* s, wchar_t* &d, int &post)
{
	int lengh = Wlen(s);
	wchar_t d1[100];
	while (post < lengh)
	{
		if (s[post++] == 8220) break;
	}
	int i = post;
	while (i < lengh&&s[i] != 8221)
	{
		d1[i - post] = s[i];
		i++;
	}
	d1[i - post] = L'\0';
	d = new wchar_t[Wlen(d1)];
	wcscpy(d, d1);
	d[Wlen(d1)] = L'\0';
	post = i + 1;
}
int Wchar_int(wchar_t* s)
{
	int k = 0;
	int lengh = Wlen(s);
	for (int i = 0; i < lengh; i++)
	{
		k = k * 10 + (s[i] - 48);
	}
	return k;
}
wchar_t * TachTen(wchar_t*S)
{
	int k = 0;
	wchar_t d[10];
	d[k++] = S[0];
	for (int i = 1; i < Wlen(S) - 1; i++)
	{
		if (S[i] == L' '&&S[i + 1] != L' ') d[k++] = S[i + 1];
	}
	d[k] = L'\0';
	for (int i = 0; i < k; i++)
	{
		if (L'A' <= d[i] && d[i] <= L'Z') d[i] = d[i] + 32;
	}
	wchar_t*s = new wchar_t[k];
	wcscpy(s, d);
	s[k] = '\0';
	return s;
}
void Thong_tin_SV(SinhVien &SV, FILE* FP)
{
	int post = 0;
	wchar_t Thong_tin[1000];
	wchar_t *s;
	fgetws(Thong_tin, 1000, FP);
	TOKen(Thong_tin, SV.MSSV, post);
	TOKen(Thong_tin, SV.HoTen, post);
	TOKen(Thong_tin, SV.Khoa, post);
	TOKen(Thong_tin, s, post);
	SV.Khoa1 = Wchar_int(s);
	TOKen(Thong_tin, SV.NgaySinh, post);
	TOKen(Thong_tin, SV.HinhAnh, post);
	TOKen(Thong_tin, SV.MoTa, post);
	int i = 0;
	while (post < Wlen(Thong_tin))
	{
		TOKen(Thong_tin, SV.Sothich.ST[i++], post);
	}
	SV.Sothich.n = i;
}
wchar_t* TenHTML(wchar_t* s)
{
	wchar_t* S1;
	wchar_t s2[10] = L".html";
	int l = Wlen(s) + 5;
	S1 = new wchar_t[l];
	wcscpy(S1, s);
	for (int i = Wlen(s); i < l; i++)
	{
		S1[i] = s2[i - Wlen(s)];
	}
	S1[l] = L'\0';
	return S1;
}
wchar_t* Ngat_Chuoi(wchar_t* Ch_nguon, wchar_t* ch_con)
{
	int post = (int)(wcsstr(Ch_nguon, ch_con) - Ch_nguon + 1);
	int l = Wlen(Ch_nguon) - post - Wlen(ch_con) + 1;// độ dài chuỗi tách
	wchar_t* d = new wchar_t[l]; //chứa chuỗi con tách từ vị trí post
	for (int i = 0; i <l; i++)
	{
		d[i] = Ch_nguon[post + Wlen(ch_con) + i - 1];
	}
	d[l] = L'\0';
	Ch_nguon[post - 1] = L'\0';
	return d;
}
void Thaythe(wchar_t *Ch_nguon, wchar_t* Ch_thaythe, wchar_t* Ch_dc_thay)
{
	wchar_t* temp;
	if (wcsstr(Ch_nguon, Ch_dc_thay) != NULL)
	{
		temp = Ngat_Chuoi(Ch_nguon, Ch_dc_thay);
		int l = Wlen(Ch_nguon);
		int h = Wlen(Ch_thaythe);
		int k = Wlen(temp);
		for (int i = 0; i < h; i++)
		{
			Ch_nguon[l + i] = Ch_thaythe[i];
		}
		for (int i = 0; i < k; i++)
		{
			Ch_nguon[l + h + i] = temp[i];
		}
		Ch_nguon[l + k + h] = L'\0';
	}
}
void XuatHTML(FILE* HTML, FILE* fp, SinhVien sv)
{
	while (!feof(HTML))
	{
		wchar_t Thong_tin[1000];
		fgetws(Thong_tin, 1000, HTML);
		if (wcsstr(Thong_tin, L"Sở thích") != NULL)
		{
			fputws(Thong_tin, fp);
			while (1)
			{
				fgetws(Thong_tin, 1000, HTML);
				fputws(Thong_tin, fp);
				if (wcsstr(Thong_tin, L"TextInList") != NULL) break;
			}
			while (1)
			{
				fgetws(Thong_tin, 1000, HTML);
				if (wcsstr(Thong_tin, L"</ul>") != NULL) break;
			}
			if (sv.Sothich.n == 0) fwprintf(fp, L"%s\n", L"<li>Không có</li>");
			else
			{
				for (int i = 0; i < sv.Sothich.n; i++)
				{
					fwprintf(fp, L"<li>%s</li>\n", sv.Sothich.ST[i]);
				}
				fwprintf(fp, L"%s\n", L"</ul>");
			}
		}
		else
		{
			Thaythe(Thong_tin, sv.HoTen, L"Nguyễn Văn A");
			Thaythe(Thong_tin, sv.HoTen, L"NGUYỄN VĂN A");
			Thaythe(Thong_tin, sv.MSSV, L"1212123");
			Thaythe(Thong_tin, sv.Khoa, L"KHOA CÔNG NGHỆ THÔNG TIN");
			Thaythe(Thong_tin, sv.Khoa, L"Công nghệ thông tin");
			Thaythe(Thong_tin, TachTen(sv.HoTen), L"nva");
			Thaythe(Thong_tin, sv.HinhAnh, L"1212123.jpg");
			Thaythe(Thong_tin, sv.NgaySinh, L"20/01/1994");
			Thaythe(Thong_tin, sv.MoTa, L"Tôi là một người rất thân thiện");
			Thaythe(Thong_tin, L"1712901", L"MSSV ");
			Thaythe(Thong_tin, L"Trần Chí Vĩ", L"Tên sinh viên thực hiện");
			fputws(Thong_tin, fp);
		}
	}
}
int main() {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	FILE* fin1 = _wfopen(L"dca.csv", L"r, ccs=UTF-8");
	if (fin1 == NULL) wprintf(L"\nKhông mở được file.\n");
	else
	{
		while (!feof(fin1))
		{
			SinhVien sv;
			FILE* fin = _wfopen(L"1212123.html", L"r, ccs=UTF-8");
			Thong_tin_SV(sv, fin1);
			FILE* fin2 = _wfopen(TenHTML(sv.MSSV), L"w, ccs=UTF-8");
			XuatHTML(fin, fin2, sv);
			fclose(fin2);
			fclose(fin);
		}
		fclose(fin1);
	}
	wprintf(L"\nChương trình kết thúc.\n");
	_getch();
	return 0;
}