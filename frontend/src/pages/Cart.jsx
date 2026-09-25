function Cart({
  cartItems,
  onIncrease,
  onDecrease,
  onRemove,
  onCheckout,
}) {
  const total = cartItems.reduce(
    (sum, item) =>
      sum + item.price * item.quantity,
    0
  );

  const totalItems = cartItems.reduce(
    (sum, item) =>
      sum + item.quantity,
    0
  );

  return (
    <div className="cart-page">
      <div className="cart-header">
        <p>GEETHAMART</p>

        <h1>Your Cart</h1>

        <span>
          Review your items before checkout
        </span>
      </div>

      <div className="cart-content">
        <div className="cart-items">
          {cartItems.length > 0 ? (
            cartItems.map((item) => (
              <div
                className="cart-item"
                key={item.id}
              >
                <div className="cart-item-image">
                  <span>{item.image}</span>
                </div>

                <div className="cart-item-info">
                  <p>{item.category}</p>

                  <h2>{item.name}</h2>

                  <strong>
                    ₹{item.price}
                  </strong>
                </div>

                <div className="cart-item-quantity">
                  <button
                    onClick={() =>
                      onDecrease(item.id)
                    }
                  >
                    -
                  </button>

                  <span>
                    {item.quantity}
                  </span>

                  <button
                    onClick={() =>
                      onIncrease(item.id)
                    }
                  >
                    +
                  </button>
                </div>

                <div className="cart-item-total">
                  ₹{item.price * item.quantity}
                </div>

                <button
                  className="remove-cart-button"
                  onClick={() =>
                    onRemove(item.id)
                  }
                >
                  Remove
                </button>
              </div>
            ))
          ) : (
            <div className="cart-empty">
              <h2>Your cart is empty</h2>

              <p>
                Add some products to your cart
                to continue shopping.
              </p>
            </div>
          )}
        </div>

        <div className="cart-summary">
          <h2>Order Summary</h2>

          <div className="summary-row">
            <span>Items</span>

            <span>{totalItems}</span>
          </div>

          <div className="summary-row">
            <span>Subtotal</span>

            <span>₹{total}</span>
          </div>

          <div className="summary-row">
            <span>Delivery</span>

            <span>Free</span>
          </div>

          <div className="summary-divider"></div>

          <div className="summary-total">
            <span>Total</span>

            <strong>₹{total}</strong>
          </div>

          <button
            className="checkout-button"
            onClick={onCheckout}
            disabled={cartItems.length === 0}
          >
            Proceed to Checkout
          </button>
        </div>
      </div>
    </div>
  );
}

export default Cart;