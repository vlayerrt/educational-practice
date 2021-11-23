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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace UsersApp
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
  /*   private static Entities context;
   public static Entities GetContext()
   {
       if (context == null)
           context = new Entities();
      return context;
    } */
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }


       private void Button_Reg_Click(object sender, RoutedEventArgs e)
        {

            string login = textboxLogin.Text.Trim();
            string pass = PassBox.Password.Trim();
            string pass_2 = PassBox_2.Password.Trim();
            string email = textboxEmail.Text.Trim().ToLower();
            textboxLogin.ToolTip = "";
            textboxLogin.Background = Brushes.Transparent;
            PassBox.ToolTip = "";
            PassBox.Background = Brushes.Transparent;
            PassBox_2.ToolTip = "";
            PassBox_2.Background = Brushes.Transparent;
            textboxEmail.ToolTip = "";
            textboxEmail.Background = Brushes.Transparent;
            if (login.Length < 5)
            {
                textboxLogin.ToolTip = "Это поле введено не корректно";
                textboxLogin.Background = Brushes.DarkRed;
            }
            else if (pass.Length <5 )
            {
               PassBox.ToolTip = "Это поле введено не корректно";
                PassBox.Background = Brushes.DarkRed;
            }
            else if (pass != pass_2)
            {
                PassBox.ToolTip = "Это поле введено не корректно";
                PassBox_2.Background = Brushes.DarkRed;
            }
            else if (pass != pass_2)
            {
                PassBox.ToolTip = "Это поле введено не корректно";
                PassBox_2.Background = Brushes.DarkRed;
            }   
             else if (email.Length <5 || !email.Contains("@") || !email.Contains("."))
            {
                textboxEmail.ToolTip = "Это поле введено не корректно";
                textboxEmail.Background = Brushes.DarkRed;
            }  
            else 
            {
               
                MessageBox.Show("Всё хорошо");
                // Создать нового покупателя
                Users user = new Users
                {
                    login = login,
                    pass = pass,
                    email = email
                };

                SFEntities.GetContext().Users.Add(user);
                SFEntities.GetContext().SaveChanges();

                AuthWindow AuthWindow = new AuthWindow();
                AuthWindow.Show();
                Hide();
            }
        }


        private void Button_Auth_Click(object sender, RoutedEventArgs e)
        {
            AuthWindow AuthWindow = new AuthWindow();
            AuthWindow.Show();
            Hide();
        }
    }
}
