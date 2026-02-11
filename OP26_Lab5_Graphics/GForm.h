#pragma once
#include <cmath> 

namespace OP26_Lab5_Graphics {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
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

	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ btnDraw;
	private: System::Windows::Forms::RadioButton^ rbTask1;
	private: System::Windows::Forms::RadioButton^ rbTask2;
	private: System::Windows::Forms::GroupBox^ grpBoxChoice;
	private: System::ComponentModel::Container^ components;

		   void InitializeComponent(void)
		   {
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->btnDraw = (gcnew System::Windows::Forms::Button());
			   this->rbTask1 = (gcnew System::Windows::Forms::RadioButton());
			   this->rbTask2 = (gcnew System::Windows::Forms::RadioButton());
			   this->grpBoxChoice = (gcnew System::Windows::Forms::GroupBox());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   this->grpBoxChoice->SuspendLayout();
			   this->SuspendLayout();

			   this->pictureBox1->BackColor = System::Drawing::Color::White;
			   this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			   this->pictureBox1->Location = System::Drawing::Point(20, 130);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(760, 430);
			   this->pictureBox1->TabIndex = 0;
			   this->pictureBox1->TabStop = false;

			   this->btnDraw->BackColor = System::Drawing::Color::DodgerBlue;
			   this->btnDraw->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->btnDraw->FlatAppearance->BorderSize = 0;
			   this->btnDraw->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->btnDraw->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
			   this->btnDraw->ForeColor = System::Drawing::Color::White;
			   this->btnDraw->Location = System::Drawing::Point(350, 40);
			   this->btnDraw->Name = L"btnDraw";
			   this->btnDraw->Size = System::Drawing::Size(180, 50);
			   this->btnDraw->TabIndex = 1;
			   this->btnDraw->Text = L"ПОБУДУВАТИ";
			   this->btnDraw->UseVisualStyleBackColor = false;
			   this->btnDraw->Click += gcnew System::EventHandler(this, &GForm::btnDraw_Click);

			   this->grpBoxChoice->Controls->Add(this->rbTask1);
			   this->grpBoxChoice->Controls->Add(this->rbTask2);
			   this->grpBoxChoice->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			   this->grpBoxChoice->Location = System::Drawing::Point(20, 20);
			   this->grpBoxChoice->Name = L"grpBoxChoice";
			   this->grpBoxChoice->Size = System::Drawing::Size(300, 90);
			   this->grpBoxChoice->TabIndex = 2;
			   this->grpBoxChoice->TabStop = false;
			   this->grpBoxChoice->Text = L" Вибір алгоритму ";

			   this->rbTask1->AutoSize = true;
			   this->rbTask1->Checked = true;
			   this->rbTask1->Location = System::Drawing::Point(20, 30);
			   this->rbTask1->Name = L"rbTask1";
			   this->rbTask1->Size = System::Drawing::Size(186, 24);
			   this->rbTask1->TabIndex = 0;
			   this->rbTask1->TabStop = true;
			   this->rbTask1->Text = L"Сплайн Ерміта";
			   this->rbTask1->UseVisualStyleBackColor = true;

			   this->rbTask2->AutoSize = true;
			   this->rbTask2->Location = System::Drawing::Point(20, 55);
			   this->rbTask2->Name = L"rbTask2";
			   this->rbTask2->Size = System::Drawing::Size(176, 24);
			   this->rbTask2->TabIndex = 1;
			   this->rbTask2->Text = L"Фрактал Коха (Квадрат)";
			   this->rbTask2->UseVisualStyleBackColor = true;

			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 20);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::FromArgb(245, 247, 250);
			   this->ClientSize = System::Drawing::Size(800, 580);
			   this->Controls->Add(this->grpBoxChoice);
			   this->Controls->Add(this->btnDraw);
			   this->Controls->Add(this->pictureBox1);
			   this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
			   this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			   this->MaximizeBox = false;
			   this->Name = L"GForm";
			   this->Text = L"Графічний редактор";
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   this->grpBoxChoice->ResumeLayout(false);
			   this->grpBoxChoice->PerformLayout();
			   this->ResumeLayout(false);
		   }

		   void DrawHermiteSpline(Graphics^ g, Pen^ pen, PointF P1, PointF P2, PointF V1, PointF V2)
		   {
			   float step = 0.001f;
			   float oldX = P1.X;
			   float oldY = P1.Y;

			   for (float t = 0; t <= 1.0; t += step)
			   {
				   float h1 = 2 * pow(t, 3) - 3 * pow(t, 2) + 1;
				   float h2 = -2 * pow(t, 3) + 3 * pow(t, 2);
				   float h3 = pow(t, 3) - 2 * pow(t, 2) + t;
				   float h4 = pow(t, 3) - pow(t, 2);

				   float x = h1 * P1.X + h2 * P2.X + h3 * V1.X + h4 * V2.X;
				   float y = h1 * P1.Y + h2 * P2.Y + h3 * V1.Y + h4 * V2.Y;

				   g->DrawLine(pen, oldX, oldY, x, y);
				   oldX = x;
				   oldY = y;
			   }
		   }

		   void DrawKochLine(Graphics^ g, Pen^ pen, PointF p1, PointF p2, int depth)
		   {
			   if (depth == 0) {
				   g->DrawLine(pen, p1, p2);
			   }
			   else {
				   float dx = p2.X - p1.X;
				   float dy = p2.Y - p1.Y;

				   PointF pA(p1.X + dx / 3.0f, p1.Y + dy / 3.0f);
				   PointF pB(p1.X + 2 * dx / 3.0f, p1.Y + 2 * dy / 3.0f);

				   double angle = -System::Math::PI / 2.0;

				   float xx = pA.X - pB.X;
				   float yy = pA.Y - pB.Y;

				   float pCx = pB.X + xx * (float)cos(angle) - yy * (float)sin(angle);
				   float pCy = pB.Y + xx * (float)sin(angle) + yy * (float)cos(angle);
				   PointF pC(pCx, pCy);

				   DrawKochLine(g, pen, p1, pA, depth - 1);
				   DrawKochLine(g, pen, pA, pC, depth - 1);
				   DrawKochLine(g, pen, pC, pB, depth - 1);
				   DrawKochLine(g, pen, pB, p2, depth - 1);
			   }
		   }

	private: System::Void btnDraw_Click(System::Object^ sender, System::EventArgs^ e) {
		if (pictureBox1->Image == nullptr) {
			pictureBox1->Image = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
		}
		Bitmap^ bmp = (Bitmap^)pictureBox1->Image;
		Graphics^ g = Graphics::FromImage(bmp);
		g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
		g->Clear(Color::White);

		if (rbTask1->Checked)
		{
			Pen^ penHermite = gcnew Pen(Color::FromArgb(0, 102, 204), 2.5f);
			PointF P1(100.0f, 215.0f), P2(660.0f, 215.0f);
			PointF V1(200.0f, -500.0f), V2(200.0f, -500.0f);

			DrawHermiteSpline(g, penHermite, P1, P2, V1, V2);
			g->FillEllipse(Brushes::Tomato, P1.X - 5.0f, P1.Y - 5.0f, 10.0f, 10.0f);
			g->FillEllipse(Brushes::Tomato, P2.X - 5.0f, P2.Y - 5.0f, 10.0f, 10.0f);
		}
		else
		{
			Pen^ penFractal = gcnew Pen(Color::FromArgb(45, 45, 45), 1.2f);
			int depth = 4;
			PointF A(280.0f, 115.0f), B(480.0f, 115.0f), C(480.0f, 315.0f), D(280.0f, 315.0f);

			DrawKochLine(g, penFractal, A, B, depth);
			DrawKochLine(g, penFractal, B, C, depth);
			DrawKochLine(g, penFractal, C, D, depth);
			DrawKochLine(g, penFractal, D, A, depth);
		}

		pictureBox1->Image = bmp;
		delete g;
	}
	};
}