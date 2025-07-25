<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Bank Management System (C++)</title>
  <style>
    body {
      font-family: 'Segoe UI', sans-serif;
      margin: 40px;
      background-color: #f9f9f9;
      color: #333;
      line-height: 1.7;
    }
    h1, h2, h3 {
      color: #005288;
    }
    code {
      background: #eee;
      padding: 2px 5px;
      border-radius: 4px;
    }
    pre {
      background: #f0f0f0;
      padding: 10px;
      overflow: auto;
      border-left: 5px solid #005288;
    }
    ul {
      margin-bottom: 20px;
    }
  </style>
</head>
<body>

  <h1>💼 Bank Management System (C++)</h1>

  <p>
    A comprehensive console-based <strong>Bank Management System</strong> developed in <code>C++</code>.
    This project simulates real-world banking operations such as user authentication, account management,
    currency handling, and transaction processing. It is ideal as an educational project for understanding
    object-oriented programming, file handling, and software architecture using C++.
  </p>

  <hr>

  <h2>📌 Features</h2>
  <ul>
    <li><strong>🔐 User Authentication & Authorization</strong>
      <ul>
        <li>Login system with role-based access (Admin / Client)</li>
        <li>Secure credential verification</li>
      </ul>
    </li>
    <li><strong>👥 User Account Management</strong>
      <ul>
        <li>Create, update, delete, and search for client accounts</li>
        <li>Unique account IDs for each user</li>
      </ul>
    </li>
    <li><strong>💳 Transaction Processing</strong>
      <ul>
        <li>Deposit, withdraw, and transfer funds between accounts</li>
        <li>Transaction logs stored for auditing</li>
      </ul>
    </li>
    <li><strong>💱 Currency Management</strong>
      <ul>
        <li>Manage and view multiple currencies with detailed attributes:</li>
        <ul>
          <li>Country name</li>
          <li>Currency name</li>
          <li>Currency code (e.g., USD, EGP)</li>
          <li>Exchange rate to USD</li>
        </ul>
        <li>Convert balances and transaction amounts between different currencies</li>
        <li>Search for currencies by code or country name</li>
        <li>Admins can add, update, or delete currencies</li>
        <li>Update exchange rates dynamically</li>
        <li><em>Example: Convert 100 EGP to USD at rate 0.032 → Result: 3.2 USD</em></li>
      </ul>
    </li>
    <li><strong>💾 Data Storage</strong>
      <ul>
        <li>Text-based file storage for user data and history</li>
        <li>Persistent client, currency, and transaction records</li>
      </ul>
    </li>
    <li><strong>📊 Reporting</strong>
      <ul>
        <li>View detailed client and transaction reports</li>
        <li>Admin activity and login logs</li>
      </ul>
    </li>
  </ul>

  <hr>

  <h2>🏗️ Project Structure</h2>

  <pre><code>
Bank-Management-System/
├── core/
│   ├── constants/
│   │   ├── file_paths/
│   │   ├── messages/
│   │   └── permissions/
│   ├── session/
│   ├── types/
│   └── utils/
│       ├── headers/
│       └── implementations/
│
├── data/
│   ├── data_source/
│   │   ├── auth/
│   │   ├── users/
│   │   ├── clients/
│   │   └── currencies/
│   ├── models/
│   └── services/
│       └── txt/
│           └── file_txt_manager/
│
├── di/
│   └── view_model_provider/
│
├── main/
│   └── main.cpp
│
├── Presentation/
│   ├── base/
│   │   └── base_screen.h
│   ├── auth/
│   │   ├── screens/
│   │   └── view_model/
│   ├── users/
│   │   ├── helpers/
│   │   ├── screens/
│   │   └── view_model/
│   ├── clients/
│   │   ├── helpers/
│   │   ├── screens/
│   │   └── view_model/
│   └── currencies/
│       ├── helpers/
│       ├── screens/
│       └── view_model/
│
├── cls_main_screen.h
│
└── Data/
    └── txt/
        ├── Users/
        ├── Clients/
        └── Currencies/
  </code></pre>

  <hr>

  <h2>🛠️ Build & Run</h2>
  <ol>
    <li>Clone the repository:<br>
      <code>git clone https://github.com/HalimWagih66/BankSystemCPP.git</code>
    </li>
    <li>Navigate into the project folder:<br>
      <code>cd BankSystemCPP</code>
    </li>
    <li>Compile the project:<br>
      <code>g++ -std=c++17 main.cpp core/**/*.cpp data/**/*.cpp Presentation/**/*.cpp -o BankSystem</code>
    </li>
    <li>Run the program:<br>
      <code>./BankSystem</code>
    </li>
  </ol>

  <hr>

  <h2>⚙️ Assumptions & Requirements</h2>
  <ul>
    <li>Console-based interface (no GUI)</li>
    <li>Works on Windows or Linux</li>
    <li>Single-user access only</li>
    <li>Text files are used for data storage</li>
    <li>Error handling is minimal</li>
  </ul>

  <hr>

  <h2>🧠 Design Notes</h2>
  <ul>
    <li>Modular codebase with separation of concerns</li>
    <li>Singleton Pattern used in managers</li>
    <li>Directory-based architecture</li>
  </ul>

  <hr>

<hr>

<h2>🔑 Default Admin Login</h2>
<p>You can log in using the following default administrator credentials:</p>
<ul>
  <li><strong>Username:</strong> Halim_Wagih</li>
  <li><strong>Password:</strong> Halim@123</li>
</ul>
<p><em>Note: These credentials are for demo/testing purposes only. For production environments, use more secure credentials.</em></p>

<hr>

  <h2>📜 License</h2>
  <p>This project is licensed under the <strong>MIT License</strong>.</p>

  <hr>

  <h2>🤝 Contributing</h2>
  <p>Pull requests are welcome. Fork the repo, make changes, and submit a PR.</p>

  <hr>

  <h2>🙏 Acknowledgments</h2>
  <p>Developed by <strong>Halim Wagih</strong> — thanks to the C++ community for tools, patterns, and best practices.</p>

</body>
</html>
