using System;
using System.Drawing;
using System.Windows.Forms;

namespace WinFormsApp1
{
    public interface IImage
    {
        void Display();
    }

    public class RealImage : IImage
    {
        private readonly string filename;

        public RealImage(string filename)
        {
            this.filename = filename;
            LoadImage();
        }

        private void LoadImage()
        {
            Console.WriteLine("Loading real image...");
        }

        public void Display()
        {
            Console.WriteLine("Displaying real image...");
        }
    }

    public class ProxyImage : IImage
    {
        private RealImage realImage;
        private readonly string filename;

        public ProxyImage(string filename)
        {
            this.filename = filename;
        }

        public void Display()
        {
            if (realImage == null)
            {
                realImage = new RealImage(filename);
            }
            realImage.Display();
        }
    }

    public class ImageEditor : Form
    {
        private readonly IImage imageProxy;
        private Button displayButton;
        private PictureBox pictureBox;

        public ImageEditor()
        {
            imageProxy = new ProxyImage("C:\\Users\\HoangGia\\Desktop\\attt\\WinFormsApp1\\TestImage.jpg");

            this.Paint += new PaintEventHandler(Form_Paint);
            this.Size = new Size(500, 500);

            // Initialize and position the button
            displayButton = new Button();
            displayButton.Text = "Display";
            displayButton.Location = new Point(250, 250);
            displayButton.Click += new EventHandler(DisplayButton_Click);
            this.Controls.Add(displayButton);

            // Initialize PictureBox
            pictureBox = new PictureBox();
            pictureBox.Location = new Point(50, 50);
            pictureBox.Size = new Size(200, 150);
            this.Controls.Add(pictureBox);
        }

        private void Form_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            Pen pen = new Pen(Color.Black);
            g.DrawRectangle(pen, 50, 50, 200, 150);
        }

       
        private void DisplayButton_Click(object sender, EventArgs e)
        {
            imageProxy.Display();
            LoadImageToPictureBox(); // Call this method after displaying the image
        }

        private void LoadImageToPictureBox()
        {
            // Load image to PictureBox
            pictureBox.Image = Image.FromFile("C:\\Users\\HoangGia\\Desktop\\attt\\WinFormsApp1\\TestImage.jpg");
        }

        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.Run(new ImageEditor());
        }
    }
}
