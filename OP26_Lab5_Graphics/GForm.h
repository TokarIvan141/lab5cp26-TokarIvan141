#pragma once
#include <cmath> 

namespace OP26_Lab5_Graphics {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class GForm : public System::Windows::Forms::Form
	{
	public:
		GForm(void)
		{
			InitializeComponent();
		}

	protected:
		~GForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::PictureBox^ pictureBox1;
		System::Windows::Forms::Button^ btnDraw;
		System::Windows::Forms::RadioButton^ rbTask1;
		System::Windows::Forms::RadioButton^ rbTask2;
		System::Windows::Forms::GroupBox^ grpBoxChoice;
		System::Windows::Forms::GroupBox^ grpParams;
		System::Windows::Forms::NumericUpDown^ nudP1x; System::Windows::Forms::NumericUpDown^ nudP1y;
		System::Windows::Forms::NumericUpDown^ nudP2x; System::Windows::Forms::NumericUpDown^ nudP2y;
		System::Windows::Forms::NumericUpDown^ nudV1x; System::Windows::Forms::NumericUpDown^ nudV1y;
		System::Windows::Forms::NumericUpDown^ nudV2x; System::Windows::Forms::NumericUpDown^ nudV2y;
		System::Windows::Forms::NumericUpDown^ nudDepth;
		System::ComponentModel::Container^ components;

		void AddInput(String^ labelText, System::Windows::Forms::NumericUpDown^% nud, int x, int y, float defVal) {
			Label^ lbl = gcnew Label();
			lbl->Text = labelText;
			lbl->Location = System::Drawing::Point(x, y);
			lbl->AutoSize = true;
			nud = gcnew NumericUpDown();
			nud->Location = System::Drawing::Point(x + 45, y - 3);
			nud->Size = System::Drawing::Size(70, 25);
			nud->Minimum = -2000;
			nud->Maximum = 2000;
			nud->Value = (Decimal)defVal;
			this->grpParams->Controls->Add(lbl);
			this->grpParams->Controls->Add(nud);
		}

		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->btnDraw = (gcnew System::Windows::Forms::Button());
			this->rbTask1 = (gcnew System::Windows::Forms::RadioButton());
			this->rbTask2 = (gcnew System::Windows::Forms::RadioButton());
			this->grpBoxChoice = (gcnew System::Windows::Forms::GroupBox());
			this->grpParams = (gcnew System::Windows::Forms::GroupBox());
			this->SuspendLayout();

			this->pictureBox1->BackColor = System::Drawing::Color::White;
			this->pictureBox1->Location = System::Drawing::Point(330, 20);
			this->pictureBox1->Size = System::Drawing::Size(730, 540);

			this->grpBoxChoice->Text = L" Алгоритм ";
			this->grpBoxChoice->Location = System::Drawing::Point(20, 20);
			this->grpBoxChoice->Size = System::Drawing::Size(290, 90);
			this->rbTask1->Checked = true;
			this->rbTask1->Text = L"Сплайн Ерміта";
			this->rbTask1->Location = System::Drawing::Point(20, 30);
			this->rbTask1->CheckedChanged += gcnew EventHandler(this, &GForm::OnModeChanged);
			this->rbTask2->Text = L"Фрактал Коха";
			this->rbTask2->Location = System::Drawing::Point(20, 55);
			this->grpBoxChoice->Controls->Add(this->rbTask1);
			this->grpBoxChoice->Controls->Add(this->rbTask2);

			this->grpParams->Text = L" Параметри ";
			this->grpParams->Location = System::Drawing::Point(20, 120);
			this->grpParams->Size = System::Drawing::Size(290, 280);

			AddInput(L"P1.x", nudP1x, 15, 40, 100.0f); AddInput(L"P1.y", nudP1y, 150, 40, 215.0f);
			AddInput(L"P2.x", nudP2x, 15, 85, 600.0f); AddInput(L"P2.y", nudP2y, 150, 85, 215.0f);
			AddInput(L"V1.x", nudV1x, 15, 145, 200.0f); AddInput(L"V1.y", nudV1y, 150, 145, -500.0f);
			AddInput(L"V2.x", nudV2x, 15, 190, 200.0f); AddInput(L"V2.y", nudV2y, 150, 190, -500.0f);

			Label^ lblD = gcnew Label(); lblD->Text = L"Глибина:"; lblD->Location = Point(15, 240);
			lblD->AutoSize = true;
			nudDepth = gcnew NumericUpDown();
			nudDepth->Location = Point(100, 237);
			nudDepth->Maximum = 6;
			nudDepth->Value = 4;
			nudDepth->Enabled = false;
			this->grpParams->Controls->Add(lblD);
			this->grpParams->Controls->Add(nudDepth);

			this->btnDraw->BackColor = System::Drawing::Color::DodgerBlue;
			this->btnDraw->FlatStyle = FlatStyle::Flat;
			this->btnDraw->ForeColor = Color::White;
			this->btnDraw->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold));
			this->btnDraw->Location = System::Drawing::Point(20, 510);
			this->btnDraw->Size = System::Drawing::Size(290, 50);
			this->btnDraw->Text = L"ПОБУДУВАТИ";
			this->btnDraw->Click += gcnew EventHandler(this, &GForm::btnDraw_Click);

			this->ClientSize = System::Drawing::Size(1080, 580);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->grpBoxChoice);
			this->Controls->Add(this->grpParams);
			this->Controls->Add(this->btnDraw);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			this->Text = L"Графіка: Лабораторна №5";
			this->ResumeLayout(false);
		}

		void OnModeChanged(Object^ s, EventArgs^ e) {
			bool h = rbTask1->Checked;
			nudP1x->Enabled = h;
			nudP1y->Enabled = h;
			nudP2x->Enabled = h;
			nudP2y->Enabled = h;
			nudV1x->Enabled = h;
			nudV1y->Enabled = h;
			nudV2x->Enabled = h;
			nudV2y->Enabled = h;
			nudDepth->Enabled = !h;
		}

		void DrawHermiteSpline(Graphics^ g, Pen^ pen, PointF P1, PointF P2, PointF V1, PointF V2)
		{
			float step = 0.001f;
			float oldX = P1.X, oldY = P1.Y;
			for (float t = 0.0f; t <= 1.0f; t += step) {
				float t2 = t * t, t3 = t2 * t;
				float h1 = 2 * t3 - 3 * t2 + 1, h2 = -2 * t3 + 3 * t2, h3 = t3 - 2 * t2 + t, h4 = t3 - t2;
				float x = h1 * P1.X + h2 * P2.X + h3 * V1.X + h4 * V2.X;
				float y = h1 * P1.Y + h2 * P2.Y + h3 * V1.Y + h4 * V2.Y;
				g->DrawLine(pen, oldX, oldY, x, y);
				oldX = x; oldY = y;
			}
		}

		void DrawKochLine(Graphics^ g, Pen^ pen, PointF p1, PointF p2, int depth)
		{
			if (depth == 0) g->DrawLine(pen, p1, p2);
			else {
				float dx = p2.X - p1.X, dy = p2.Y - p1.Y;
				PointF pA(p1.X + dx / 3.0f, p1.Y + dy / 3.0f), pB(p1.X + 2 * dx / 3.0f, p1.Y + 2 * dy / 3.0f);
				double angle = -System::Math::PI / 2.0;
				float xx = pA.X - pB.X, yy = pA.Y - pB.Y;
				PointF pC(pB.X + xx * (float)cos(angle) - yy * (float)sin(angle), pB.Y + xx * (float)sin(angle) + yy * (float)cos(angle));
				DrawKochLine(g, pen, p1, pA, depth - 1); DrawKochLine(g, pen, pA, pC, depth - 1);
				DrawKochLine(g, pen, pC, pB, depth - 1); DrawKochLine(g, pen, pB, p2, depth - 1);
			}
		}

	private: System::Void btnDraw_Click(System::Object^ sender, System::EventArgs^ e) {
		if (pictureBox1->Image == nullptr) pictureBox1->Image = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
		Bitmap^ bmp = (Bitmap^)pictureBox1->Image;
		Graphics^ g = Graphics::FromImage(bmp);
		g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
		g->Clear(Color::White);

		if (rbTask1->Checked) {
			Pen^ p = gcnew Pen(Color::DodgerBlue, 2.5f);
			PointF P1((float)nudP1x->Value, (float)nudP1y->Value);
			PointF P2((float)nudP2x->Value, (float)nudP2y->Value);
			PointF V1((float)nudV1x->Value, (float)nudV1y->Value);
			PointF V2((float)nudV2x->Value, (float)nudV2y->Value);
			DrawHermiteSpline(g, p, P1, P2, V1, V2);
			g->FillEllipse(Brushes::Tomato, P1.X - 5.0f, P1.Y - 5.0f, 10.0f, 10.0f);
			g->FillEllipse(Brushes::Tomato, P2.X - 5.0f, P2.Y - 5.0f, 10.0f, 10.0f);
		}
		else {
			Pen^ p = gcnew Pen(Color::Black, 1.0f);
			int d = (int)nudDepth->Value;
			PointF A(250.0f, 150.0f), B(450.0f, 150.0f), C(450.0f, 350.0f), D(250.0f, 350.0f);
			DrawKochLine(g, p, A, B, d); DrawKochLine(g, p, B, C, d); DrawKochLine(g, p, C, D, d); DrawKochLine(g, p, D, A, d);
		}
		pictureBox1->Image = bmp;
		delete g;
	}
	};
}