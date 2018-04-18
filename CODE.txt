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
	post = i+1;
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
void Thong_tin_SV(SinhVien &SV, FILE* FP)
{
	int post = 0;
	wchar_t username[1000];
	wchar_t *s;
	fgetws(username, 1000, FP);
	TOKen(username, SV.MSSV, post);
	TOKen(username, SV.HoTen, post);
	TOKen(username, SV.Khoa, post);
	TOKen(username, s, post);
	SV.Khoa1 = Wchar_int(s);
	TOKen(username, SV.NgaySinh, post);
	TOKen(username, SV.HinhAnh, post);
	TOKen(username, SV.MoTa, post);
	int i = 0;
	while (post < Wlen(username))
	{
		TOKen(username, SV.Sothich.ST[i++], post);
	}
	SV.Sothich.n = i;
}
void Xuat_thongTin(SinhVien SV)
{
	wchar_t* khoa;
	fputws(SV.MSSV, stdout);
	fputws(SV.HoTen, stdout);
	fputws(SV.Khoa, stdout);
	fputws(SV.NgaySinh, stdout);
	fputws(SV.HinhAnh, stdout);
	fputws(SV.MoTa, stdout);
	for (int i = 0; i < SV.Sothich.n; i++)
	{
		fputws(SV.Sothich.ST[i], stdout);
	}
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
int main() {
	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
	_setmode(_fileno(stdin), _O_U16TEXT); //needed for input
	FILE* fin = _wfopen(L"dca.csv", L"r, ccs=UTF-8");
	if (fin == NULL) wprintf(L"\nChương trình kết thúc.\n");
	else
	{
		while (!feof(fin))
		{
			SinhVien sv;
			Thong_tin_SV(sv, fin);
			Xuat_thongTin(sv);
			FILE* fin2 = _wfopen(TenHTML(sv.MSSV), L"w, ccs=UTF-8");
			if (fin2 == NULL) wprintf(L"không mở đươc file");
			else
			{
				fwprintf(fin2, L"<!DOCTYPE html PUBLIC \" -//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd \" >\n");
				fwprintf(fin2, L"<html xmlns=\"http://www.w3.org/1999/xhtml \">\n\t<head>\n\t\t<meta http-equiv=\"Content - Type\" content=\"text/html; charset = utf - 8\" />\n");
				fwprintf(fin2, L"\t\t<link rel=\"stylesheet\" type=\"text/css\" href=\"personal.css\" />\n\t\t<title>HCMUS - %s</title>\n\t</head>\n\t<body>\n\t\t<div class=\"Layout_container\">\n", sv.HoTen);
				fwprintf(fin2, L"\t\t\t<!-- Begin Layout Banner Region -->\n\t\t\t<div class=\"Layout_Banner\" >\n\t\t\t\t<div><img id=\"logo\" src=\"Images/logo.jpg\" height=\"105\" /></div>\n");
				fwprintf(fin2, L"\t\t\t\t<div class=\"Header_Title\">TRƯỜNG ĐẠI HỌC KHOA HỌC TỰ NHIÊN </div>\n\t\t\t</div>\n\t\t\t<!-- End Layout Banner Region -->\n\t\t\t<!-- Begin Layout MainContents Region -->\n\t\t\t<div class=\"Layout_MainContents\">\n");
				fwprintf(fin2, L"\t\t\t\t<!-- Begin Below Banner Region -->\n\t\t\t\t<div class=\"Personal_Main_Information\">\n\t\t\t\t\t<div class=\"Personal_Location\">\n");
				fwprintf(fin2, L"\t\t\t\t\t\t<img src=\"Images/LogoFooter.jpg\" width=\"27\" height=\"33\" />\n\t\t\t\t\t\t<span class=\"Personal_FullName\">%s - %d</span>\n", sv.HoTen, sv.MSSV);
				fwprintf(fin2, L"\t\t\t\t\t\t<div class=\"Personal_Department\">%s</div>\n\t\t\t\t\t\t<br />\n\t\t\t\t\t\t<div class=\"Personal_Phone\">\n\t\t\t\t\t\t\tEmail: nva@gmail.com\n", sv.Khoa);
				fwprintf(fin2, L"\t\t\t\t\t\t</div>\n\t\t\t\t\t\t<br />\n\t\t\t\t\t\t<br />\n\t\t\t\t\t</div>\n\t\t\t\t\t<div class=\"Personal_HinhcanhanKhung\">\n\t\t\t\t\t\t<img src=\"Images/%s\" class=\"Personal_Hinhcanhan\" />\n", sv.HinhAnh);
				fwprintf(fin2, L"\t\t\t\t\t</div>\n\t\t\t\t</div>\n\t\t\t\t<!-- End Below Banner Region -->\n\t\t\t\t<!-- Begin MainContents Region -->\n\t\t\t\t<div class=\"MainContain\">\n\n\t\t\t\t\t<!-- Begin Top Region -->\n\t\t\t\t\t<div class=\"MainContain_Top\">\n\n");
				fwprintf(fin2, L"\t\t\t\t\t\t<div class=\"InfoGroup\">Thông tin cá nhân</div>\n\t\t\t\t<div>\n\t\t\t\t\t<ul class=\"TextInList\">\n\t\t\t\t\t\t<li>Họ và tên: %s</li>\n", sv.HoTen);
				fwprintf(fin2, L"\t\t\t\t\t\t\t\t<li>MSSV: %s</li>\n\t\t\t\t\t\t\t\t<li>Sinh viên khoa %s</li>\n\t\t\t\t\t\t\t\t<li>Ngày sinh: %s</li>\n\t\t\t\t\t\t\t\t<li>Email: nva@gmail.com</li>\n\t\t\t\t\t\t\t</ul>\n", sv.MSSV, sv.Khoa, sv.NgaySinh);
				fwprintf(fin2, L"\t\t\t\t\t\t</div>\n\t\t\t\t<div class=\"InfoGroup\">Sở thích</div>\n\t\t\t\t<div>\n\t\t\t\t\t<ul class=\"TextInList\">");
				for (int i = 0; i < sv.Sothich.n; i++)
				{
					fwprintf(fin2, L"<li>%s", sv.Sothich.ST[i]);
				}
				fwprintf(fin2, L"</ul>");
				fwprintf(fin2, L"\t\t\t\t\t\t</div>\n\t\t\t\t\t\t<div class=\"InfoGroup\">Mô tả</div>\n\t\t\t\t\t\t<div class=\"Description\">\n\t\t\t\t\t%s.\n\t\t\t\t\t\t</div>\n\n\t\t\t\t</div>\n\t\t\t</div>\n\t\t<d/iv>\n\n\t\t<!-- Begin Layout Footer -->\n", sv.MoTa);
				fwprintf(fin2, L"\t\t\t<!-- Begin Layout Footer -->\n\t\t\t<div class=\"Layout_Footer\">\n\t\t\t\t<div class=\"divCopyright\">\n\t\t\t\t\t<br />\n\t\t\t\t\t<img src=\"Images/LogoFooter_gray.jpg\" width=\"34\" height=\"41\" /><br />\n\t\t\t\t\t<br />\n\t\t\t\t\t@2013</br>\n\t\t\tĐồ án giữ kỳ</br>\n");
				fwprintf(fin2, L"\t\t\tKỹ thuật lập trình</br>\n\t\t\tTH2018/03</br>\n\t\t\t1712901 - Trần Chí Vĩ </br>\n\t\t\t</div>\n\t\t\t</div>\n\t\t\t<!-- End Layout Footer -->\n\t\t</div>\n\t</body>\n</html>");
				fclose(fin2);
			}
			fclose(fin2);
			wprintf(L"\nChương trình kết thúc ooo.\n");
		}
		fclose(fin);
	}
	_getch();
	return 0;
}s