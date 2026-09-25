import { useState } from 'react';

function Checkout() {
  const [cartItems] = useState(() => {
    return (
      JSON.parse(
        localStorage.getItem('geethaMartCart')
      ) || []
    );
  });

  const [fullName, setFullName] = useState('');
  const [email, setEmail] = useState('');
  const [phone, setPhone] = useState('');
  const [address, setAddress] = useState('');
  const [city, setCity] = useState('');
  const [pincode, setPincode] = useState('');
  const [payment, setPayment] = useState('COD');

  const [error, setError] = useState('');
  const [orderPlaced, setOrderPlaced] =
    useState(false);

  const subtotal = cartItems.reduce(
    (sum, item) =>
      sum + item.price * item.quantity,
    0
  );

  const totalItems = cartItems.reduce(
    (sum, item) =>
      sum + item.quantity,
    0
  );

  const handleSubmit = (event) => {
    event.preventDefault();

    setError('');

    if (cartItems.length === 0) {
      setError(
        'Your cart is empty. Please add products before checkout.'
      );
      return;
    }

    if (
      fullName.trim() === '' ||
      email.trim() === '' ||
      phone.trim() === '' ||
      address.trim() === '' ||
      city.trim() === '' ||
      pincode.trim() === ''
    ) {
      setError(
        'Please fill in all delivery details.'
      );
      return;
    }

    if (!/^\d{10}$/.test(phone)) {
      setError(
        'Please enter a valid 10-digit phone number.'
      );
      return;
    }

    if (!/^\d{6}$/.test(pincode)) {
      setError(
        'Please enter a valid 6-digit PIN code.'
      );
      return;
    }

    localStorage.removeItem(
      'geethaMartCart'
    );

    setOrderPlaced(true);
  };

  if (orderPlaced) {
    return (
      <div className="checkout-page">
        <div className="checkout-success">
          <div className="checkout-success-icon">
            ✓
          </div>

          <h1>Order Placed Successfully!</h1>

          <p>
            Thank you, {fullName}. Your GeethaMart
            order has been placed successfully.
          </p>

          <div className="checkout-success-details">
            <p>
              <strong>Total Items:</strong>{' '}
              {totalItems}
            </p>

            <p>
              <strong>Total Amount:</strong>{' '}
              ₹{subtotal}
            </p>

            <p>
              <strong>Payment:</strong>{' '}
              {payment === 'COD'
                ? 'Cash on Delivery'
                : 'Online Payment'}
            </p>
          </div>

          <button
            className="checkout-button"
            onClick={() =>
              window.location.reload()
            }
          >
            Continue Shopping
          </button>
        </div>
      </div>
    );
  }

  return (
    <div className="checkout-page">
      <div className="checkout-header">
        <p>GEETHAMART</p>

        <h1>Checkout</h1>

        <span>
          Complete your order
        </span>
      </div>

      <div className="checkout-content">
        <div className="checkout-form-card">
          <h2>Delivery Details</h2>

          {error && (
            <div className="checkout-error">
              {error}
            </div>
          )}

          <form
            className="checkout-form"
            onSubmit={handleSubmit}
          >
            <div className="form-group">
              <label htmlFor="full-name">
                Full Name
              </label>

              <input
                id="full-name"
                type="text"
                placeholder="Enter your full name"
                value={fullName}
                onChange={(event) =>
                  setFullName(
                    event.target.value
                  )
                }
              />
            </div>

            <div className="form-group">
              <label htmlFor="email">
                Email Address
              </label>

              <input
                id="email"
                type="email"
                placeholder="Enter your email"
                value={email}
                onChange={(event) =>
                  setEmail(
                    event.target.value
                  )
                }
              />
            </div>

            <div className="form-group">
              <label htmlFor="phone">
                Phone Number
              </label>

              <input
                id="phone"
                type="tel"
                placeholder="Enter 10-digit phone number"
                value={phone}
                onChange={(event) =>
                  setPhone(
                    event.target.value
                  )
                }
              />
            </div>

            <div className="form-group">
              <label htmlFor="address">
                Delivery Address
              </label>

              <input
                id="address"
                type="text"
                placeholder="Enter your delivery address"
                value={address}
                onChange={(event) =>
                  setAddress(
                    event.target.value
                  )
                }
              />
            </div>

            <div className="checkout-row">
              <div className="form-group">
                <label htmlFor="city">
                  City
                </label>

                <input
                  id="city"
                  type="text"
                  placeholder="Enter city"
                  value={city}
                  onChange={(event) =>
                    setCity(
                      event.target.value
                    )
                  }
                />
              </div>

              <div className="form-group">
                <label htmlFor="pincode">
                  PIN Code
                </label>

                <input
                  id="pincode"
                  type="text"
                  placeholder="Enter 6-digit PIN"
                  value={pincode}
                  onChange={(event) =>
                    setPincode(
                      event.target.value
                    )
                  }
                />
              </div>
            </div>

            <div className="form-group">
              <label htmlFor="payment">
                Payment Method
              </label>

              <select
                id="payment"
                value={payment}
                onChange={(event) =>
                  setPayment(
                    event.target.value
                  )
                }
              >
                <option value="COD">
                  Cash on Delivery
                </option>

                <option value="ONLINE">
                  Online Payment
                </option>
              </select>
            </div>

            <button
              type="submit"
              className="place-order-button"
            >
              Place Order
            </button>
          </form>
        </div>

        <div className="checkout-summary">
          <h2>Order Summary</h2>

          {cartItems.map((item) => (
            <div
              className="checkout-item"
              key={item.id}
            >
              <div className="checkout-item-image">
                <span>{item.image}</span>
              </div>

              <div className="checkout-item-info">
                <h3>{item.name}</h3>

                <p>
                  ₹{item.price} ×{' '}
                  {item.quantity}
                </p>
              </div>

              <strong>
                ₹{item.price * item.quantity}
              </strong>
            </div>
          ))}

          <div className="checkout-divider"></div>

          <div className="summary-row">
            <span>Items</span>

            <span>{totalItems}</span>
          </div>

          <div className="summary-row">
            <span>Subtotal</span>

            <span>₹{subtotal}</span>
          </div>

          <div className="summary-row">
            <span>Delivery</span>

            <span>Free</span>
          </div>

          <div className="summary-divider"></div>

          <div className="summary-total">
            <span>Total</span>

            <strong>₹{subtotal}</strong>
          </div>
        </div>
      </div>
    </div>
  );
}

export default Checkout;