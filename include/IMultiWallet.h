// Copyright (c) 2012-2015, The CryptoNote developers, The Bytecoin developers
//
// This file is part of Bytecoin.
//
// Bytecoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Bytecoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Bytecoin.  If not, see <http://www.gnu.org/licenses/>.

// Copyright (c) 2012-2014, The CryptoNote developers, The Bytecoin developers
//
// This file is part of Bytecoin.
//
// Bytecoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Bytecoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Bytecoin.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <array>
#include <vector>

namespace CryptoNote {

enum class MultiWalletTransactionState : uint8_t {
  FAILED
};

struct MultiWalletTransaction {
  MultiWalletTransactionState state;
  uint64_t timestamp;
  uint64_t blockHeight;
  std::array<uint8_t, 32> hash;
  bool isBase;
  int64_t totalAmount;
  uint64_t fee;
  uint64_t creationTime;
  uint64_t unlockTime;
  std::string extra;
};

struct MultiWalletTransfer {
  std::string address;
  uint64_t amount;
};

class IMultiWallet {
public:
  virtual ~IMultiWallet() {}

  virtual void initialize(const std::string& password) = 0;
  virtual void load(std::istream& source, const std::string& password) = 0;
  virtual void shutdown() = 0;

  virtual void changePassword(const std::string& oldPassword, const std::string& newPassword) = 0;
  virtual void save(std::ostream& destination, bool saveDetails = true, bool saveCache = true) = 0;

  virtual std::size_t getAddressCount() const = 0;
  virtual std::string getAddress(std::size_t index) const = 0;
  virtual std::string createAddress() = 0;
  virtual std::string createAddress(const std::array<uint8_t, 32>& spendPublicKey, const std::array<uint8_t, 32>& spendSecretKey) = 0;
  virtual void deleteAddress(const std::string& address) = 0;

  virtual uint64_t getActualBalance() const = 0;
  virtual uint64_t getActualBalance(const std::string& address) const = 0;
  virtual uint64_t getPendingBalance() const = 0;
  virtual uint64_t getPendingBalance(const std::string& address) const = 0;

  virtual std::size_t getTransactionCount() const = 0;
  virtual MultiWalletTransaction getTransaction(std::size_t transactionIndex) const = 0;
  virtual std::size_t getTransactionTransferCount(std::size_t transactionIndex) const = 0;
  virtual MultiWalletTransfer getTransactionTransfer(std::size_t transactionIndex, std::size_t transferIndex) const = 0;

  virtual std::size_t transfer(const MultiWalletTransfer& destination, uint64_t fee, uint64_t mixIn = 0, const std::string& extra = "", uint64_t unlockTimestamp = 0) = 0;
  virtual std::size_t transfer(const std::vector<MultiWalletTransfer>& destinations, uint64_t fee, uint64_t mixIn = 0, const std::string& extra = "", uint64_t unlockTimestamp = 0) = 0;
  virtual std::size_t transfer(const std::string& sourceAddress, const MultiWalletTransfer& destination, uint64_t fee, uint64_t mixIn = 0, const std::string& extra = "", uint64_t unlockTimestamp = 0) = 0;
  virtual std::size_t transfer(const std::string& sourceAddress, const std::vector<MultiWalletTransfer>& destinations, uint64_t fee, uint64_t mixIn = 0, const std::string& extra = "", uint64_t unlockTimestamp = 0) = 0;

  virtual void start() = 0;
  virtual void stop() = 0;
  virtual void refresh() = 0;
};

}
