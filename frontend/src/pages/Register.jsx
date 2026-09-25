import { useState } from 'react';

function Register({ onLogin }) {
  const [name, setName] = useState('');
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const [role, setRole] = useState('BUYER');

  const handleSubmit = (event) => {
    event.preventDefault();

    console.log('Registration form submitted');
    console.log('Name:', name);
    console.log('Email:', email);
    console.log('Password:', password);
    console.log('Role:', role);
  };

  return (
    <div className="login-page">
      <div className="login-card">
        <div className="login-header">
          <div className="login-logo">🛒</div>

          <h1>Create Account</h1>

          <p>
            Register for your GeethaMart account
          </p>
        </div>

        <form onSubmit={handleSubmit}>
          <div className="form-group">
            <label htmlFor="name">
              Full Name
            </label>

            <input
              id="name"
              type="text"
              placeholder="Enter your full name"
              value={name}
              onChange={(event) =>
                setName(event.target.value)
              }
              required
            />
          </div>

          <div className="form-group">
            <label htmlFor="register-email">
              Email Address
            </label>

            <input
              id="register-email"
              type="email"
              placeholder="Enter your email"
              value={email}
              onChange={(event) =>
                setEmail(event.target.value)
              }
              required
            />
          </div>

          <div className="form-group">
            <label htmlFor="register-password">
              Password
            </label>

            <input
              id="register-password"
              type="password"
              placeholder="Create a password"
              value={password}
              onChange={(event) =>
                setPassword(event.target.value)
              }
              required
            />
          </div>

          <div className="form-group">
            <label htmlFor="role">
              Account Type
            </label>

            <select
              id="role"
              value={role}
              onChange={(event) =>
                setRole(event.target.value)
              }
            >
              <option value="BUYER">
                Buyer
              </option>

              <option value="SELLER">
                Seller
              </option>
            </select>
          </div>

          <button
            type="submit"
            className="login-button"
          >
            Create Account
          </button>
        </form>

        <p className="register-text">
          Already have an account?{' '}

          <button
            type="button"
            onClick={onLogin}
            style={{
              border: 'none',
              background: 'none',
              padding: 0,
              color: '#166534',
              fontWeight: '600',
              cursor: 'pointer',
              fontSize: '14px',
            }}
          >
            Login
          </button>
        </p>
      </div>
    </div>
  );
}

export default Register;