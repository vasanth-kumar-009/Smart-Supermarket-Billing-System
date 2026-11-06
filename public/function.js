'use strict';
    // Mirrors Bill, addItem(), and printBill() from the original C++ console app.
    const KEY = 'supermarket-billing-cpp-demo-inventory-v1';
    function loadInventory() {
      try {
        const value = JSON.parse(localStorage.getItem(KEY) || '[]');
        if (!Array.isArray(value)) return [];
        return value.filter(x => x && typeof x.item === 'string' && Number.isSafeInteger(x.rate) && x.rate >= 0 && Number.isSafeInteger(x.quantity) && x.quantity >= 0);
      } catch { return []; }
    }
    let inventory = loadInventory();
    let bill = [];
    const $ = id => document.getElementById(id);
    const money = n => '₹' + n.toLocaleString('en-IN');
    const text = (tag, content) => { const el = document.createElement(tag); el.textContent = content; return el; };
    function saveInventory() { try { localStorage.setItem(KEY, JSON.stringify(inventory)); return true; } catch { return false; } }
    function notify(id, message, error = false) { $(id).textContent = message; $(id).classList.toggle('error', error); }
    function renderInventory() {
      const target = $('inventoryTable'); target.replaceChildren();
      if (!inventory.length) { target.append(text('div', 'No items in inventory yet.')); return; }
      const wrap = document.createElement('div'); wrap.className = 'tablewrap';
      const table = document.createElement('table'); const head = document.createElement('thead');
      const hrow = document.createElement('tr');['Item', 'Rate', 'Quantity'].forEach(v => hrow.append(text('th', v))); head.append(hrow); table.append(head);
      const body = document.createElement('tbody');
      for (const item of inventory) { const tr = document.createElement('tr');[item.item, money(item.rate), String(item.quantity)].forEach(v => tr.append(text('td', v))); body.append(tr); }
      table.append(body); wrap.append(table); target.append(wrap);
      const datalist = $('itemsList'); datalist.replaceChildren();
      for (const item of inventory) { const opt = document.createElement('option'); opt.value = item.item; datalist.append(opt); }
    }
    function renderBill() {
      const target = $('receiptItems'); target.replaceChildren();
      if (!bill.length) { target.className = 'empty'; target.textContent = 'No items added to this bill yet.'; } else {
        target.className = 'tablewrap'; const table = document.createElement('table');
        const head = document.createElement('thead'), tr = document.createElement('tr');
        ['Item', 'Rate', 'Qty', 'Amount'].forEach(v => tr.append(text('th', v))); head.append(tr); table.append(head);
        const body = document.createElement('tbody');
        for (const x of bill) { const row = document.createElement('tr');[x.item, money(x.rate), String(x.quantity), money(x.rate * x.quantity)].forEach(v => row.append(text('td', v))); body.append(row); }
        table.append(body); target.append(table);
      }
      $('totalAmount').textContent = money(bill.reduce((sum, x) => sum + x.rate * x.quantity, 0));
    }
    for (const b of document.querySelectorAll('[data-view]')) {
      b.addEventListener('click', () => {
        const view = b.dataset.view;
        for (const v of ['add', 'bill', 'inventory']) $(v + 'Panel').hidden = (v !== view);
        document.querySelectorAll('[data-view]').forEach(btn => btn.classList.toggle('active', btn === b));
        renderInventory();
      });
    }
    $('addForm').addEventListener('submit', e => {
      e.preventDefault();
      const item = $('itemName').value.trim(), rate = Number($('itemRate').value), quantity = Number($('itemQuantity').value);
      if (!item || /[\s:]/.test(item) || !Number.isSafeInteger(rate) || rate < 0 || !Number.isSafeInteger(quantity) || quantity <= 0) { notify('addMessage', 'Enter a single-word name, a nonnegative whole-number rate, and a positive whole-number quantity.', true); return; }
      // The original C++ app appends a new record for every add, including duplicate names.
      inventory.push({ item, rate, quantity });
      const saved = saveInventory(); renderInventory(); $('addForm').reset();
      notify('addMessage', `${item} added successfully (${quantity} at ${money(rate)} each).${saved ? '' : ' Browser storage is unavailable; changes will last only for this page.'}`);
    });
    $('billForm').addEventListener('submit', e => {
      e.preventDefault();
      const item = $('purchaseItem').value.trim(), quantity = Number($('purchaseQuantity').value);
      if (!item || !Number.isSafeInteger(quantity) || quantity <= 0) { notify('billMessage', 'Enter a valid item and a positive whole-number quantity.', true); return; }
      // Like the C++ file scan, process every matching inventory record individually.
      const matches = inventory.filter(x => x.item === item);
      if (!matches.length) { notify('billMessage', 'Item Not Available!', true); return; }
      let sold = 0;
      for (const stock of matches) {
        if (quantity <= stock.quantity) {
          stock.quantity -= quantity;
          bill.push({ item: stock.item, rate: stock.rate, quantity }); sold++;
        }
      }
      if (!sold) { notify('billMessage', `Sorry, ${item} Ended! Requested quantity exceeds available stock.`, true); return; }
      const saved = saveInventory(); renderInventory(); renderBill();
      notify('billMessage', `${item} added to the bill.${saved ? '' : ' Warning: browser storage is unavailable.'}`);
      $('billForm').reset(); $('purchaseQuantity').value = '1';
    });
    $('clearBill').addEventListener('click', () => {
      if (bill.length && !confirm('Close this billing session? The receipt will be cleared, but inventory deductions will remain.')) return;
      bill = []; renderBill(); notify('billMessage', 'Session closed. Start a new bill.'); $('receiptStatus').textContent = 'Thanks for shopping!';
    });
    $('printBill').addEventListener('click', () => { if (!bill.length) { alert('Add an item to the bill first.'); return; } window.print(); });
    $('resetInventory').addEventListener('click', () => { if (!confirm('Delete all saved inventory items?')) return; inventory = []; saveInventory(); renderInventory(); });
    renderInventory(); renderBill();