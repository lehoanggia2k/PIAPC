namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form_MouseDoubleClick(object? sender, MouseEventArgs e)
        {
            MessageBox.Show("Double-click detected!");
        }
    }
}