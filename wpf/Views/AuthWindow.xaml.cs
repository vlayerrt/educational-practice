using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace UsersApp
{
    /// <summary>
    /// Логика взаимодействия для AuthWindow.xaml
    /// </summary>
    public partial class AuthWindow : Window
    {
        public AuthWindow()
        {
            InitializeComponent();
        }

        private void Button_Auth_Click(object sender, RoutedEventArgs e)
        {
            string login = textboxLogin.Text.Trim();
            string pass = PassBox.Password.Trim();
            if (login.Length < 5)
            {
                textboxLogin.ToolTip = "Это поле введено не корректно";
                textboxLogin.Background = Brushes.DarkRed;
            }
            else if (pass.Length < 5)
            {
                PassBox.ToolTip = "Это поле введено не корректно";
                PassBox.Background = Brushes.DarkRed;
            }
            else
            {
                textboxLogin.ToolTip = "";
                textboxLogin.Background = Brushes.Transparent;
                PassBox.ToolTip = "";
                PassBox.Background = Brushes.Transparent;

                List<Users> Users = SFEntities.GetContext().Users.Where(b => b.login == login && b.pass == pass).ToList();
                if (Users.Count != 0)
                {
                    MessageBox.Show("Все Хорошо!");
                    UserPageWindow userPageWindow = new UserPageWindow();
                    userPageWindow.Show();
                    Hide();
                }
                else MessageBox.Show("Неверные данные");
            }
        }

        private void Button_Reg_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWindow = new MainWindow();
            mainWindow.Show();
            Hide();
        }
    }
}
