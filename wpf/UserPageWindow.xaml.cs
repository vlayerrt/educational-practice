﻿using System;
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
    /// Логика взаимодействия для UserPageWindow.xaml
    /// </summary>
    public partial class UserPageWindow : Window
    {

        public UserPageWindow()
        {
            InitializeComponent();

            List<Users> Users = SFEntities.GetContext().Users.ToList();
            listOfUsers.ItemsSource = Users;
        }
/*        public override string ToString()
        {
            return "Пользователь: " + login + ". Email: " + email;
        }*/
    }
}
